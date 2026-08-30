*This project has been created as part of the 42 curriculum by kong.*

## Description

This project is a four-exercise introduction to C++ inheritance, built around a small family of robots descended from a base class called `ClapTrap`. Each exercise adds one more layer of inheritance complexity on top of the last:

| Exercise | Class | Inherits from | New concept introduced |
|---|---|---|---|
| ex00 | `ClapTrap` | — | Encapsulation, constructors/destructor, member functions |
| ex01 | `ScavTrap` | `ClapTrap` | Single inheritance, constructor/destructor chaining |
| ex02 | `FragTrap` | `ClapTrap` | A sibling branch of the same base class |
| ex03 | `DiamondTrap` | `ScavTrap` **and** `FragTrap` | Multiple inheritance, the diamond problem, virtual inheritance |

The goal isn't the robots themselves — it's using them as a small, observable playground for the mechanics of C++ inheritance: what gets constructed when, what a subclass can and can't touch on its parent, and what changes once a class has more than one parent.

## Instructions

Each exercise lives in its own directory with its own `Makefile`. All code is compiled with `c++ -Wall -Wextra -Werror -std=c++98`.

```bash
cd ex00   # or ex01, ex02, ex03
make      # builds the binary
./claptrap    # ex00
./scavtrap    # ex01
./fragtrap    # ex02
./diamondtrap # ex03

make clean    # remove object files
make fclean   # remove object files and the binary
make re       # fclean + all
```

Each `main.cpp` is a self-written test suite exercising: default/named construction, energy/hit-point exhaustion, KO and "passed out" guards, copy construction/assignment, and — from ex01 onward — construction/destruction chaining, so the message order printed to stdout can be read directly as a trace of what got built and destroyed, in what order.

## Technical Concepts

- **Member-initializer list vs. constructor body.** The initializer list (`Ctor() : member(value) { }`) is where a member's *initial* value is set, before the constructor body runs. Anything not listed there is default-constructed first, then can be reassigned in the body. This matters for correctness with primitive types like `int`: a member left out of the list isn't "zero by default" the way it might be in C — it's left with an indeterminate value.

  ```cpp
  // Bug we hit in ex00: no init list, no message, and _hp/_ep/_dmg
  // are left uninitialized (undefined behavior on first use).
  ClapTrap::ClapTrap() {};

  // Fixed: every member has a defined starting value.
  ClapTrap::ClapTrap() : _name("Default"), _hp(10), _ep(10), _dmg(0)
  {
      std::cout << "Default constructor called" << std::endl;
  }
  ```

- **`private` vs. `protected`.** `private` members are invisible even to a subclass; `protected` extends visibility to derived classes while still hiding them from outside code. `ClapTrap`'s attributes start `private` in ex00 (correct there — nothing inherits from it yet), but the moment `ScavTrap` needs to set its own hit points in ex01, `private` has to become `protected`, or the derived class simply cannot see the members it needs to touch.

- **A derived class's initializer list cannot target inherited members** — this one is easy to get wrong and not obvious from the error message alone. Access level and "can this appear in my initializer list" are two separate rules.

  ```cpp
  // Illegal, even with _hp declared protected in ClapTrap:
  // error: class 'ScavTrap' does not have any field named '_hp'
  ScavTrap::ScavTrap() : _hp(100) { }
  ```
  A constructor's initializer list may only name its *direct* base classes (to call their constructor) or members declared *directly* in that class. `_hp` belongs to `ClapTrap`, not `ScavTrap` — `ScavTrap` doesn't "have" it, it inherits the subobject. The fix is to let the base build itself first, then override in the constructor *body*:
  ```cpp
  ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
  {
      _hp = 100;
      _ep = 50;
      _dmg = 20;
      std::cout << "ScavTrap Constructor called" << std::endl;
  }
  ```

- **Construction/destruction chaining.** A derived object's base part must exist before the derived part can be built on top of it, so bases always construct *first*. Destruction is the exact mirror — the derived part might still rely on the base being intact while it tears itself down, so it's destroyed *first*, and the base goes last. This is directly observable in our test output:

  ```
  ClapTrap Constructor called
  ScavTrap Constructor called
  ...
  ScavTrap Destructor called
  ClapTrap Destructor called
  ```

- **Function hiding, not overriding.** `ScavTrap::attack()` and `FragTrap::attack()` don't *override* `ClapTrap::attack()` in the polymorphic sense (nothing here is `virtual` at the function level) — they *hide* it. Calling `attack()` on a `ScavTrap&` or a `ScavTrap` object always resolves to `ScavTrap::attack`, resolved statically by the compiler based on the declared type, not a vtable lookup. This project doesn't need true runtime polymorphism, so this distinction doesn't bite here — but it's worth knowing it's a different mechanism from `virtual` dispatch.

- **The diamond problem.** `DiamondTrap` inherits from both `ScavTrap` and `FragTrap`, each of which inherits from `ClapTrap`. Without any special handling, `DiamondTrap` would contain **two independent `ClapTrap` subobjects** — one via each parent path — with two separate copies of `_name`/`_hp`/`_ep`/`_dmg`, and any unqualified access to them becomes ambiguous.

  ```cpp
  class ScavTrap : public ClapTrap { ... };   // ClapTrap copy #1
  class FragTrap : public ClapTrap { ... };   // ClapTrap copy #2
  class DiamondTrap : public ScavTrap, public FragTrap { ... }; // two ClapTraps!
  ```

- **Virtual inheritance — the fix.** Marking the shared base `virtual` collapses every inheritance path back to it into a single shared subobject:

  ```cpp
  class ScavTrap : virtual public ClapTrap { ... };
  class FragTrap : virtual public ClapTrap { ... };
  class DiamondTrap : public ScavTrap, public FragTrap { ... }; // exactly one ClapTrap
  ```
  This is what the subject means by *"the ClapTrap instance of DiamondTrap will be created once, and only once."*

- **Who actually constructs a virtual base.** This is the part of virtual inheritance that isn't obvious from the keyword alone: a virtual base is always constructed by the constructor of the **most-derived (complete) object type** — never by an intermediate parent — regardless of how many levels removed it is. 
Grandchild Takes Control: The most derived class (the grandchild) becomes directly responsible for initializing the virtual base (the grandparent).

Concretely, when building a `DiamondTrap`:
  1. The compiler looks at `DiamondTrap`'s own initializer list for a mem-initializer targeting `ClapTrap` (its *grandparent*) and uses that to build the one shared subobject, **first**, before anything else.
  2. Then `ScavTrap`'s and `FragTrap`'s own constructors run — but any attempt inside *their* initializer lists to build `ClapTrap` is silently discarded, because it's already built. Only the rest of their bodies actually execute.

  | Step | What runs | What's discarded |
  |---|---|---|
  | 1 | `DiamondTrap`'s `ClapTrap(...)` call | — |
  | 2 | `ScavTrap`'s constructor body | `ScavTrap`'s own `: ClapTrap(...)` |
  | 3 | `FragTrap`'s constructor body | `FragTrap`'s own `: ClapTrap(...)` |
  | 4 | `DiamondTrap`'s own constructor body | — |

  Because steps 2 and 3 write into the *same shared* `_hp`/`_ep`/`_dmg` storage, each one overwrites the last. The subject asks for a deliberate mix — hit points and damage from `FragTrap`, energy points from `ScavTrap` — which no construction order alone can produce (whichever base runs last wins *all three* fields, not a hand-picked subset). The only reliable fix is to explicitly reassert the exact required values in `DiamondTrap`'s own body, after both parents have already run and clobbered each other:
  ```cpp
  DiamondTrap::DiamondTrap(const std::string& name)
      : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name)
  {
      _hp = 100;   // matches both parents
      _ep = 50;    // must be reasserted — FragTrap's body just set it to 100
      _dmg = 30;   // FragTrap's value
  }
  ```

- **Name hiding across the diamond.** The subject requires `DiamondTrap` to declare its *own* `_name` member, separate from `ClapTrap::_name`. Once it does, something non-obvious happens: **every unqualified `_name` used inside `DiamondTrap`'s own methods now refers to `DiamondTrap`'s member, not `ClapTrap`'s** — even though `ClapTrap::_name` is `protected` and would otherwise be reachable. Declaring a member with the same name as an inherited one *hides* the inherited one for unqualified lookup within that scope.

  ```cpp
  void DiamondTrap::whoAmI()
  {
      std::cout << "My name is " << _name                 // DiamondTrap's own _name
                 << ", my grandfather name is " << ClapTrap::_name  // must qualify explicitly
                 << std::endl;
  }
  ```
  Forgetting the `ClapTrap::` qualifier was a real bug we hit — both halves of the sentence printed the same value until the second `_name` was explicitly qualified.

- **Ambiguous member lookup under multiple inheritance.** `DiamondTrap` inherits `attack()` from both `ScavTrap` and `FragTrap`, and neither hides the other (they're siblings, not stacked). Calling `diamondtrap.attack(...)` without `DiamondTrap` declaring its own `attack()` fails to compile with *"request for member 'attack' is ambiguous."* The fix, matching what the subject specifies ("attack() (ScavTrap)"), is for `DiamondTrap` to declare its own `attack()` that explicitly forwards to the intended parent:
  ```cpp
  void DiamondTrap::attack(const std::string& target)
  {
      ScavTrap::attack(target);
  }
  ```

### Final attribute values, by class

| Class | Hit points | Energy points | Attack damage |
|---|---|---|---|
| `ClapTrap` | 10 | 10 | 0 |
| `ScavTrap` | 100 | 50 | 20 |
| `FragTrap` | 100 | 100 | 30 |
| `DiamondTrap` | 100 (FragTrap) | 50 (ScavTrap) | 30 (FragTrap) |

## Resources

- [cppreference — Constructors and member initializer lists](https://en.cppreference.com/w/cpp/language/constructor)
- [cppreference — Virtual base classes / multiple inheritance](https://en.cppreference.com/w/cpp/language/derived_class)
- [cppreference — Order of initialization of base and member subobjects](https://en.cppreference.com/w/cpp/language/initializer_list)
- Bjarne Stroustrup, *The C++ Programming Language* (4th ed.) — chapters on class hierarchies and multiple inheritance
- The 42 CPP Module 03 subject PDF (`en.subject.pdf`, this repository)

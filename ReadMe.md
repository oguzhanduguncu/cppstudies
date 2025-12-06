# Modern C++ Idiom: `explicit` + `emplace_back`

This document explains the design rationale and technical behavior
behind using `explicit` constructors together with `emplace_back` in
Modern C++.

------------------------------------------------------------------------

## 1. Why `explicit`?

The `explicit` keyword prevents unintended **implicit type
conversions**. It ensures that objects can only be created through
**direct initialization**.

This avoids: - Silent type conversions - Unexpected overload selection -
Subtle runtime bugs caused by unintended temporary objects

In API design, `explicit` is a **safety gate**.

------------------------------------------------------------------------

## 2. `push_back` vs `emplace_back` --- Conceptual Difference

### Object-based insertion (`push_back`)

-   Requires a fully constructed object of type `T`
-   Construction happens **outside the container**
-   The container only performs a **copy or move**

### Argument-based construction (`emplace_back`)

-   Accepts constructor arguments directly
-   Object is constructed **directly inside container memory**
-   Enables **perfect forwarding**
-   Eliminates unnecessary temporaries

------------------------------------------------------------------------

## 3. How `explicit` Changes `push_back` Behavior

When a constructor is marked `explicit`, the following is **forbidden**:

-   Implicit conversion from argument to object
-   Silent temporary materialization

This means `push_back` can **no longer rely on implicit construction**.
You must either: - Explicitly construct the object - Or use
`emplace_back`

This enforces **intentional object creation**.

------------------------------------------------------------------------

## 4. Why `explicit` + `emplace_back` Works Together

`emplace_back` performs **direct initialization** using constructor
arguments. Direct initialization is **allowed with explicit
constructors**.

So this combination gives:

-   Safety from implicit conversions (`explicit`)
-   Performance from in-place construction (`emplace_back`)
-   Clear semantic intent

This is why these two features are often used **together** in modern
APIs.

------------------------------------------------------------------------

## 5. Type Deduction vs Perfect Forwarding

-   `push_back` expects an object of type `T`

-   Type conversion must already be complete before the call

-   `emplace_back` accepts `Args&&...`

-   Constructor overload resolution happens **inside the container**

-   This enables:

    -   Safer overload selection
    -   Better control over narrowing conversions
    -   Forwarding of value categories (lvalue/rvalue)

------------------------------------------------------------------------

## 6. Design-Level Interpretation

Feature          Design Meaning
  ---------------- --------------------------------------------
`explicit`       Prevent accidental construction
`push_back`      Insert an already-existing object
`emplace_back`   Construct an object intentionally in place

Together they express a **modern design contract**: \> "Objects must be
created consciously, not implicitly."

------------------------------------------------------------------------

## 7. When This Idiom Is Especially Important

This pattern is heavily used in:

-   Standard Library container implementations
-   Game engines
-   Audio/DSP engines
-   High-performance memory-sensitive systems
-   API and library boundary design

Where: - Safety - Predictability - Performance are simultaneously
required.

------------------------------------------------------------------------

## 8. Rule of Thumb

-   Use `explicit` for single-argument constructors.
-   Use `emplace_back` when you want in-place construction.
-   Avoid relying on implicit temporary creation with `push_back`.

This combination represents **Modern C++ best practice**.

------------------------------------------------------------------------

## 9. Core Takeaway

`explicit` prevents accidental object creation. `emplace_back` enables
intentional, efficient object construction.

Used together, they form a **safe, expressive, and high-performance
container insertion idiom**.

------------------------------------------------------------------------

### References
- Scott Meyers, *Effective Modern C++*
  - Item 41 — Consider using `emplace` instead of `insert`
  - Item 25 — Use `std::move` on rvalue references, `std::forward` on universal references
  - Item 26 — Avoid overloading on universal references
  - Item 30 — Familiarize yourself with perfect forwarding failure cases


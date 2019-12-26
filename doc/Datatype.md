## Datatypes

This list is the list of builtin datatypes in WSOM expressed as their
identifier in Visual Urlang, with corresponding size in memory:

 * Byte (1 byte)
   - One byte of data.
 * Boolean (1 byte)
   - True or False
 * Integer (2 byte)
   - A normal-sized integer
 * Long (4 byte)
   - A long integer
 * LongLong (8 byte)
   - A very long integer
 * Word (word size of host processor)
   - The native word size of the host CPU.
 * Single (4 byte)
   - Like the `float` in C
 * Double (8 byte)
   - Like the `double` in C
 * Character (4 byte)
   - A character of text.
 * Date (8 byte)
   - A date and time.
 * Object (as Word)
   - A WSOM object handle.
 * Variant (Word + 12 byte)
   - 

Additionally these may become other types. Consider these:

 * `Dim x As Ptr To t`
   - Creates a Pointer to type `t`
 * `Dim x (1 To 5) As Integer`
   - Creates an array of five elemnts (1, 2, 3, 4, and 5) of Integers

You may define a new type to be a name for another. This is how String is
defined by the Visual Urlang Standard Class Library (SCL)

 * `TypeDim String() As Character`

You may define a new composite type:

```vb6
Public Type Worker
    ChristianName As String
    SirName As String
    DateOfBirth As Date
End Type
```

You may define a new instance of a Class Module. If that Class Module has a
Functor then you will argument the Functor:
```vb6
Dim a_set As Set(Integer)
```


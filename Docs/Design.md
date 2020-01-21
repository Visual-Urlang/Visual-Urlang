## Design Decisions Diary

#### 21/01/2020 2
Generics are difficult. Here is my current idea. For these two classes:

```vbnet
Class Object
End Class

Class Container (Of T)
    Inherits Object

    Dim mem As T

    Function T() As T
    End Function
End Class

Class X (Of T)
    Inherits Object

    Dim hkt As T (Of Integer)
End Class
```

What shall we get?

Perhaps this 'template' first for typechecking, let us say, X:

```
struct TypeParam
{
    String name,
    Type * type,
};

struct TypeParamRef
{
    
}

struct GenericTypeInst
{
    Array<GenericTypeInst *> supers;
    Class * name;
    Array<TypeParam *> params;
};
```

```

Container Prototype = GenericTypeInst { 
    super:
            GenericTypeInst {
                super: NULL, 
                name: Object 
            };,
    name: Container,
    params: { TypeParam { name: A, type: Object } }
};

```

```

X Prototype = GenericTypeInst { 
    super:
            GenericTypeInst {
                super: NULL, 
                name: Object 
            };,
    name: X,
    params: { TypeParam { name: T, type: Object } }
};

```

To create X prototype:
 - X will register all the iVars and methods of its class within it. In doing so,
   it will replace all references to any of its TypeParams with a special
   TypeParamPlaceholder.
 - It will tell its supers to construct similar ones, and pass the type arguments
   specified for them; they in turn will replace any reference to their own TypeParams
   with TypeParamPlaceholders given by X. They in turn will register their own iVars
   and methods.
 - This creates the Prototype.

To type-check X itself:
 - Copy X prototype. Substitute copy's TypeParams to their most permissive form. This
   likely means a lot of AnyObject types substituted in. 


#### 21/01/2020 1
I have to consider what nested classes will be implemented as. Here is what I
think I will do: a nested class will be a static member of a class. Consider:

```vbnet
Class Container (Of T)
    'Contained's "Of T" is not related to Container's "Of T".
    Class Contained (Of T)
        Dim ContainedVar As T
    End Class

    'Create a Contained of whatever Container's concrete T parameter is.
    Dim ContainerVar As Contained (Of T)
End Class
```

I believe this is the right way to do it. But what if we really want instance
variables of a class, that are a nested class? Maybe we must to think of that
as a different issue. And let this be done:

```vbnet
Class Container (Of T)
    Dim ContainedClass As Class(Of T)
End Class
```

What we do here is say that instance variable ContainedClass is of the type of
a Class which takes one argument T.

What about a class nested within a function? Here it become tricky. I believe
in such a case, we are talking about defining a whole new class. Let us leave
it for another time!
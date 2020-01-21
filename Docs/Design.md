## Design Decisions Diary

#### 21/01/2020
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
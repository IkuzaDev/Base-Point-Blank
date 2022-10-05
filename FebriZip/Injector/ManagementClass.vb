
Class ManagementClass

    Private _p1 As String

    Sub New(ByVal p1 As String)
        ' TODO: Complete member initialization 
        _p1 = p1
    End Sub

    Function Item(ByVal p1 As String) As Boolean
        Throw New NotImplementedException
    End Function

    Function GetInstances() As Menu.MenuItemCollection
        Throw New NotImplementedException
    End Function

End Class

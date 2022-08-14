object BasicObj: TForm1
  inherited MyObj0: TMyObject
  end
  inline MyObj1: TMyObject
    object MyObj2: Namespace.TMyObject
      inline MyObj3: Long.Name.Space.Example.Obj.Here.TMyObject
      end
      inherited MyObj4: Short.A.B.C.D.E.F.G.TMyObject
      end
      object MyObj5: Short.A.B.C.D.E.F.G.TMyObject2
      end
    end
  end
end

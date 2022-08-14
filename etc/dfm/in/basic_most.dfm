object BasicMost: TForm1
object Basic: TForm1
end
object BasicArray: TForm1
  Array0 = <
    item
      A = 1
    end
    item
      A = 3
      B = 4
    end
    item
      A = 5
      B = 6
      C = 7
    end>
  Array1 = <
    item
      A = 'A'
    end
    item
      A = 'B'
      B = 4
    end
    item
      A = 5
      B = 'C'
      C = clConstExample
    end>
end
object BasicArray: TForm1
  Array0 = <
    item
      A = 1
    end
    item
      A = 3
      B = 4
    end
    item
      A = 5
      B = 6
      C = 7
    end>
  Array1 = <
    item
      A = 'A'
    end
    item
      A = 'B'
      B = 4
    end
    item
      A = 5
      B = 'C'
      C = clConstExample
    end>
end
object BasicBinary: TForm1
  ByteTest = {00FF01FF00FF}
  ByteLNTest = {00
  FF
  01
  FF
  00
  FF}
  ByteLongTest = {
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F}
  ByteLongTest2 = 
  {
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
      000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F
}
  ByteLongTest3 = {000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F}
end
object BasicBit: TForm1
  Bit0 = True
  Bit1 = TRue
  Bit2 = TrUe
  Bit3 = TruE
  Bit4 = true
  Bit5 = False
  Bit6 = FAlse
  Bit7 = FaLse
  Bit8 = FalSe
  Bit9 = FalsE
  BitA = FALSE
  BitB = fAlSe
  BitC = FaLsE
end
object BasicConstant: TForm1
  Const0 = lbConstLabel
  Const1 = lbConstLabel
  Const2 = ExampleConstant
end
object BasicDateTime: TForm1
 dt0 = 0d
 dt1 = 123d
 dt2 = 1.5d
 dt3 = -2d
 dt4 = -1.5d
 dt5 = 36500d
 dt6 = 0d
end
object BasicFloat: TForm1
  Float0 = 1.0
  Float1 = 0.1
  Float2 = 0.0
  Float3 = -0001.0
  Float4 = -1
  Float5 = +5
  Float6 = 50000
  Float7 = -50000
  Float8 = 000000.0000001
end
object BasicInlineObject: TForm1
  Obj0 = ( 1 2 3 4 5 6 7 8 9 )
  Obj1 = ( $1 $2 $3 $4 $5 $6 $7 $8 $9 )
  Obj2 = ()
  Obj3 = ( $FF 'FF' {FF} -255 +1.0 +1.5 -1.0 -1.5 clExample )
  Obj4 = ( ( ( ) ) )
  Obj5 = ( ( ( clExample ) ) )
end
object BasicInt: TForm1
  IntTest0 = -10
  IntTest1 = 10
  IntTest2 = 010
  IntTest3 = $FF
  IntTest4 = $F
end
object BasicObj: TForm1
  object MyObj0: TMyObject
  end
  object MyObj1: TMyObject
    object MyObj2: Namespace.TMyObject
      object MyObj3: Long.Name.Space.Example.Obj.Here.TMyObject
      end
      object MyObj4: Short.A.B.C.D.E.F.G.TMyObject
      end
    end
  end
end
object BasicSet: TForm1
  Set0 = []
  Set1 = [1]
  Set2 = [1,2]
  Set3 = [1,2,2.5,$FF]
  Set4 = [clLabel0, clLabel1, clLabel2]
end
object BasicString: TForm1
  Str0 = ''
  Str1 = '123'
  Str2 = 'ABC'
  Str3 = 'öäü'
  Str4 = #50
  Str5 = #$50
  Str6 = #50#50#50
  Str7 = #$50#$50#$50
  Str8 = ''#$0D''
  Str9 = ''#$0D
  StrA = #$0D''
  StrB = ''#$0D'' + 'ABC'
  StrC = 'ABC'+'DEF'+''+''#$0D
  StrD = ''''
  StrE = ''''+''''
  StrF = ''''+''''#$0D
  Str10 = #$0D''''+''''
end
object BasicStrings: TForm1
  Str0 = ('')
  Str1 = ('123')
  Str2 = ('ABC')
  Str3 = ('öäü')
  Str4 = (#50)
  Str5 = (#$50)
  Str6 = (#50#50#50)
  Str7 = (#$50#$50#$50)
  Str8 = (''#$0D'')
  Str9 = (''#$0D)
  StrA = (#$0D'')
  StrB = (''#$0D'' + 'ABC')
  StrC = ('ABC'+'DEF'+''+''#$0D)
  StrD = ('''')
  StrE = (''''+'''')
  StrF = (''''+''''#$0D)
  Str10 = (#$0D''''+'''')
  Str11 = ()
  Str12 = (''
  ''
  ''
  '')
  Str13 = (''+
  ''+
  ''+
  '')
  Str14 = (''+
  ''
  ''+
  '')
  Str15 = (''+
  ''+
  ''
  '')
end
end

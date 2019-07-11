program cekPascal;

var
   x : integer;
   a : integer;
   z : integer;

begin
   x := 10;
   a := 11;
   if(a>3)then
        x:= 4;

   z := x + a;
   writeln(z);
   readln;
end.
program cekPascal;

var
   x : integer;
   a : integer;
   z : integer;
   s : string;

begin
   x := 10;
   a := 11 > 5;
   s := 'imam dwi cahyo';
   if(a>3)then
        x:= 4 + 100000;

   for i:= 1 to x do
		x:=x+1*x;
   z := x + a;
   readln;
end.
#This Code is written in SageMath 9.0

from sage.crypto.util import ascii_to_bin

def Polynomial(k,l):  #To convert ith row of lattice to a polynomial
    y = 0
    for m in range(k.nrows()):
        y += k[l,m]* x^m
    return y

R.<x> = PolynomialRing(ZZ) #Creating  ring of Polynomials over Z

def Algorithm(New_poly,d,X,N,g): # Implements the algorithm wriiten in the report and the paper.
    New_poly = New_poly.change_ring(ZZ)  #Changing polynomial ring form Zn to Z.
    x = New_poly.parent().gen()
    degree = New_poly.degree()
    dimension = degree*d
    mat = matrix(ZZ,dimension,dimension)
    f = x
    for i in range (dimension):
        for j in range (dimension):
            v = floor(i/degree)
            u = i - degree*v
            t = (f^u)*(New_poly^v)
            mat[i,j] = t[j]*(N^(d-1-v))*(X^j)
    
    b = mat
    b = b.LLL()

    mode = 1
    if (mode):
        b = b.transpose()

        for i in range(b.nrows()):
            b[i] /= X^i

        b = b.transpose()

        c = Polynomial(b,0)
        a = c.roots()
        if (a):
            #Gives the values of roots found and corresponding value of g
            print("g = ",g)
            print("The root in decimal is ",a[0][0])
            print("The root in binary is ",a[0][0].binary())

def main():
    N = 84364443735725034864402554533826279174703893439763343343863260342756678609216895093779263028809246505955647572176682669445270008816481771701417554768871285020442403001649254405058303439906229201909599348669565697534331652019516409514800265887388539283381053937433496994442146419682027649079704982600857517093
    C = 23701787746829110396789094907319830305538180376427283226295906585301889543996533410539381779684366880970896279018807100530176651625086988655210858554133345906272561027798171440923147960165094891980452757852685707020289384698322665347609905744582248157246932007978339129630067022987966706955482598869800151693
    e = 5
    p = "You see a Gold-Bug in one corner. It is the key to a treasure found by"
    p_bin = str(ascii_to_bin(p))
    p_10 = ZZ('0b'+p_bin)  #converts binary to base-10
    
    ZmodN = Zmod(N);
    
    for g in range(1, 308):
        P_10.<M> = PolynomialRing(ZmodN)  #constructing polynomial ring over Zn
        New_poly = ((p_10<<g)+ M)^e - C  #constructing the polynomial (p_10*(2^g)+ M)^e - C
        
        X = floor((N^(1/9).n()))
        d = 3
        Algorithm(New_poly,d,X,N,g)
 
main()
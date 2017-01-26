/*
 Colin McDaniel
 February 18, 2013
 
 This program prompts the user to input integers and binary code, stores the information in a BinaryInteger class, and performs different operations on the information and outputs it to the screen.
 */

#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>

using namespace std;

class BinaryInteger{
public:
    
    // Constructors
    BinaryInteger();
    BinaryInteger(int n);
    BinaryInteger(vector<bool> binary, bool sign);
    
    // Get-r
    vector<bool> getVec() const;
    
    // Print
    void print_binary();
    
    // Member operators
    BinaryInteger operator<< (int n);
    BinaryInteger operator>> (int n);
    BinaryInteger& operator<<= (int n);
    BinaryInteger& operator>>= (int n);
    
    // Friend functions
    friend BinaryInteger operator+ (BinaryInteger& a, BinaryInteger& b);
    friend BinaryInteger operator- (BinaryInteger& a, BinaryInteger& b);
    friend BinaryInteger operator& (BinaryInteger a, BinaryInteger b);
    friend BinaryInteger operator| (BinaryInteger a, BinaryInteger b);
    friend BinaryInteger operator^ (BinaryInteger a, BinaryInteger b);
    friend BinaryInteger operator~ (BinaryInteger a);
    friend ostream& operator<< (ostream& out, const BinaryInteger& a);
    
private:
    
    // Represents integer value in binary
    vector<bool> b;
    
    // Represents sign of integer
    bool s;
    
    // Private member function
    void CleanUp();
};

// Operator declarations
BinaryInteger operator+ (BinaryInteger& a, BinaryInteger& b);
BinaryInteger operator- (BinaryInteger& a, BinaryInteger& b);
BinaryInteger operator& (BinaryInteger a, BinaryInteger b);
BinaryInteger operator| (BinaryInteger a, BinaryInteger b);
BinaryInteger operator^ (BinaryInteger a, BinaryInteger b);
BinaryInteger operator~ (BinaryInteger a);
ostream& operator<< (ostream& out, const BinaryInteger& a);
istream& operator>> (istream& in, BinaryInteger& a);


int main(){
    
    // Prompts user to input integer n and prints binary representation
    cout << "Please input an integer n: ";
    BinaryInteger n;
    cin >> n;
    cout << "The binary representation for n is: ";
    n.print_binary();
    
    // Prompts user to input integer m and prints binary representation
    cout << endl << "Please input an integer m: ";
    BinaryInteger m;
    cin >> m;
    cout << "The binary representation for m is: ";
    m.print_binary();
    
    // Prompts user to input binary representation r
    cout << endl << "Please input binary representation, where the first bit indicates sign ('1' means '-'). Enter -1 when finished:" << endl;
    vector<bool> vec;
    int s;
    
    // User's first input is sign
    cin >> s;
    
    // Stores user's binary information
    int bin_rep = 0;
    while(bin_rep != -1){
        cin >> bin_rep;
        
        if(bin_rep != -1){
            switch(bin_rep){
                case 0: vec.push_back(0); break;
                case 1: vec.push_back(1); break;
                default: cout << "Invalid input. Please try again." << endl; break;
            }
        }
    }
    
    // Prints integer r
    BinaryInteger r(vec, s);
    cout << "Your integer value for r is: " << r << endl;
    
    // Prints n integer and binary
    cout << "n = " << n << " = ";
    n.print_binary();
    
    // Prints ~n in integer and binary
    cout << endl << "~n = " << (~n) << " = ";
    (~n).print_binary();
    
    // Prints n+m in integer and binary
    cout << endl << "n+m = " << n + m << " = ";
    (n + m).print_binary();
    
    // Prints n&m in integer and binary
    cout << endl << "n&m = " << (n & m) << " = ";
    (n & m).print_binary();
    
    // Prints n^r in integer and binary
    cout << endl << "n^r = " << (n ^ r) << " = ";
    (n ^ r).print_binary();
    
    // Prints 2*r in integer and binary
    cout << endl << "2r = " << (r << 1) << " = ";
    (r << 1).print_binary();
    
    // Prints n-m in integer and binary
    cout << endl << "n-m = " << n - m << " = ";
    (n - m).print_binary();
    
    // Prints n|m in integer and binary
    cout << endl << "n | m = " << (n | m) << " = ";
    (n | m).print_binary();
    
    // Prints 256*n in integer and binary
    cout << endl << "256*n = " << (n << 8) << " = ";
    (n << 8).print_binary();
    
    // Prints n/8 in integer and binary
    cout << endl << "n/8 = " << (n >> 3) << " = ";
    (n >> 3).print_binary();
    
	cout << endl << endl;
    
    return 0;
}

/** Default constructor, initializes vector of bools and sets sign to 0 when called */
BinaryInteger::BinaryInteger(){
    s = 0;
}

/** Constructor that takes integer argument and converts it to binary
 @param n Integer to be converted
 */
BinaryInteger::BinaryInteger(int n){
    
    // Stores sign
    if(n < 0){
        s = 1;
        n *= -1;
    }
    else
        s = 0;
    
    // Stores integer value in private variable b
    if(n == 0)
        b.push_back(0);
    else{
        int highest_pow = 0;
        int test = 0;
        
        // Tests for highest power of 2
        while(test <= n){
            test = pow(2.0, highest_pow);
            ++highest_pow;
        }
        highest_pow -= 2;
        
        // Stores binary representation of integer in vector b
        for(int i = highest_pow; i >= 0; i--){
            if(n / pow(2.0, i) >= 1){
                b.push_back(1);
                n %= static_cast<int>(pow(2.0, i));
            }
            else
                b.push_back(0);
        }
    }
}

/** Constructor that takes a vector of booleans argument and sign and stores it in BinaryInteger class
 @param binary Vector of booleans to be stored
 @param sign Sign of integer
 */
BinaryInteger::BinaryInteger(vector<bool> binary, bool sign){
    
    // Stores sign
    if(sign == 1)
        s = 1;
    else if(sign == 0)
        s = 0;
    
    // Stores binary in private variable b
    for(int i = 0; i < binary.size(); i++){
        b.push_back(binary[i]);
    }
}

/** Returns binary representation stored in the private vector variable
 @return b Private variable b of BinaryInteger class
 */
vector<bool> BinaryInteger::getVec() const{
    return b;
}

/** Binary print function that prints each element of the vector of bools separated by commas and enclosed by parentheses */
void BinaryInteger::print_binary(){
    int size = static_cast<int>(b.size());
    
    // Prints negative sign if necessary
    if(s == 1)
        cout << "-";
    
    // Prints vector of bools seperated by commas and enclosed by parentheses
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "(";
        
        cout << b[i];
        
        if(i == size - 1)
            cout << ")";
        else
            cout << ",";
    }
    return;
}

/** Bit shift operator that bit shifts left as many times as specified by the integer argument
 @param n Number of times to be bit shifted
 @return a BinaryInteger object bit shifted the number of times as specified
 */
BinaryInteger BinaryInteger::operator<< (int n){
    int size = static_cast<int>(b.size());
    
    // Clone private variable b
    vector<bool> clone_vec(size);
    for(int i = 0; i < size; i++)
        clone_vec[i] = b[i];
    
    // Bit shift left
    for(int i = 0; i < n; i++)
        clone_vec.push_back(0);
    
    // Create BinaryInteger object with bit-shifted vector
    BinaryInteger a(clone_vec, s);
    
    // Remove any extra zeros and signs and return object
    a.CleanUp();
    return a;
}

/** Bit shift operator that bit shifts right as many times as specified by the integer argument
 @param n Number of times to be bit shifted
 @return BinaryInteger object bit shifted the number of times as specified
 */
BinaryInteger BinaryInteger::operator>> (int n){
    int size = static_cast<int>(b.size());
    
    // Clone private variable b to vector
    vector<bool> clone_vec(size);
    for(int i = 0; i < size; i++)
        clone_vec[i] = b[i];
    
    // If number of bitshifts equals or outnumbers the number of elements, clone_vec becomes 0
    if(n >= size){
        clone_vec[0] = 0;
        for(int i = 0; i < size - 1; i++)
            clone_vec.pop_back();
    }
    else{
        
        // Bit shift right
        for(int i = 0; i < n; i++)
            clone_vec.pop_back();
    }
    
    // Create BinaryInteger object with bit-shifted vector
    BinaryInteger c(clone_vec, s);
    
    // Remove any extra zeros and signs and return object
    c.CleanUp();
    return c;
}

/** Bit shift left equals operator that bit shifts left as many times as specified and replaces old object with the updated object
 @param n Number of times to be bit shifted
 @return *this Updated BinaryInteger object
 */
BinaryInteger& BinaryInteger::operator<<= (int n){
    for(int i = 0; i < n; i++)
        b.push_back(0);
    
    this->CleanUp();
    
    return *this;
}

/** Bit shift right equals operator that bit shifts right as many times as specified and replaces old object with the updated object
 @param n Number of times to be bit shifted
 @return *this Updated BinaryInteger object
 */
BinaryInteger& BinaryInteger::operator>>= (int n){
    
    // If number of bit shifts equals or outnumbers number of elements, set value as (positive) 0
    if(n >= b.size()){
        s = 0;
        b.resize(1);
        b[0] = 0;
    }
    else{
        
        // Bit shift left
        for(int i = 0; i < n; i++)
            b.pop_back();
    }
    
    return *this;
}

/** Private member function that eliminates any unncessary 0s and negative signs in the binary expansion */
void BinaryInteger::CleanUp(){
    int size = static_cast<int>(b.size());
    int counter = 0;
    for(int i = 0; i < size - 1; i++){
        if(b[0] == 0 && counter == 0)
            b.erase(b.begin());
        else
            ++counter;
    }
    
    // Special case of -0
    if(b.size() == 1 && b[0] == 0)
        s = 0;
    
    return;
}

/** + operator for two BinaryInteger objects, performs bitwise addition on the vector of bools and returns a BinaryInteger object with this vector and the appropriate sign
 @param a Left side BinaryInteger object
 @param b Right side BinaryInteger object
 @return sum BinaryInteger representing a+b
 */
BinaryInteger operator+ (BinaryInteger& a, BinaryInteger& b){
    BinaryInteger sum;
    
    // If one BinaryInteger is positive and the other is negative, return the difference of the two
    if(a.s == 0 && b.s == 1){
        BinaryInteger b_positive(b.b, 0);
        sum = a - b_positive;
    }
    else if(a.s == 1 && b.s == 0){
        BinaryInteger a_positive(a.b, 0);
        sum = b - a_positive;
    }
    else{
        
        // Set appropriate sign
        bool sign;
        if(a.s == 0 && b.s == 0)
            sign = 0;
        else if (a.s == 1 && b.s == 1)
            sign = 1;
        
        // Allocate larger and smaller vectors
        int larger_size;
        int smaller_size;
        vector<bool> larger_vec;
        vector<bool> smaller_vec;
        if(a.b.size() < b.b.size()){
            larger_size = static_cast<int>(b.b.size());
            smaller_size = static_cast<int>(a.b.size());
            for(int i = 0; i < larger_size; i++)
                larger_vec.push_back(b.b[i]);
            for(int i = 0; i < smaller_size; i++)
                smaller_vec.push_back(a.b[i]);
        }
        else{
            larger_size = static_cast<int>(a.b.size());
            smaller_size = static_cast<int>(b.b.size());
            for(int i = 0; i < larger_size; i++)
                larger_vec.push_back(a.b[i]);
            for(int i = 0; i < smaller_size; i++)
                smaller_vec.push_back(b.b[i]);
        }
        
        // Create vector of ints for sum of bools with larger vector size plus one extra element in case of a carry-over
        vector<int> v(larger_size + 1, 0);
        
        // Add bool values together and store resulting integers in vector v
        for(int i = 0; i < smaller_size; i++)
            v[larger_size - i] = smaller_vec[smaller_size - 1 - i] + larger_vec[larger_size - 1 - i];
        
        // Fill in remaining of bool values from larger vector as integers in vector v
        for(int i = 0; i < larger_size - smaller_size; i++)
            v[larger_size - smaller_size - i] = larger_vec[larger_size - smaller_size - 1 - i];
        
        // Manipulate remainders (values 2 or higher) so that all ints in v are either 0 or 1
        for(int i = larger_size; i > 0; i--){
            if(v[i] >= 2){
                v[i - 1] += 1;
                v[i] -= 2;
            }
        }
        
        // Convert ints in v to booleans
        vector<bool> sum_vec;
        for(int i = 0; i < larger_size + 1; i++)
            sum_vec.push_back(v[i]);
        
        sum = BinaryInteger(sum_vec, sign);
    }
    
    // Remove any extra zeros and return object
    sum.CleanUp();
    return sum;
}

/** - operator for two BinaryInteger objects, performs bitwise one's complement subtraction on the objects and returns a BinaryInteger object
 @param a Left side BinaryInteger object
 @param b Right side BinaryInteger object
 @return diff BinaryInteger representing a-b
 */
BinaryInteger operator- (BinaryInteger& a, BinaryInteger& b){
    BinaryInteger diff;
    
    // If a positive and b negative, diff = a+b
    if(a.s == 0 && b.s == 1){
        BinaryInteger b_positive(b.b, 0);
        diff = a + b_positive;
    }
    
    // If a negative and b positive, diff = (-a)+(-b)
    else if(a.s == 1 && b.s == 0){
        BinaryInteger b_negative(b.b, 1);
        diff = a + b_negative;
    }
    
    // Recursion: If a and b are both negative, diff = b-a
    else if(a.s == 1 && b.s == 1){
        BinaryInteger a_positive(a.b, 0);
        BinaryInteger b_positive(b.b, 0);
        diff = b_positive - a_positive;
    }
    
    // If a and b are both positive...
    else{
        int b_size = static_cast<int>(b.b.size());
        int larger_size;
        if(a.b.size() > b.b.size())
            larger_size = static_cast<int>(a.b.size());
        else
            larger_size = static_cast<int>(b.b.size());
        
        // Create b_clone vector with one extra element at beginning to hold sign
        vector<bool> b_clone(larger_size + 1, 0);
        
        // Copy b.b into b_clone
        for(int i = 0; i < b_size; i++)
            b_clone[larger_size - i] = b.b[b_size - 1 - i];
        
        // Negates b_clone
        for(int i = 0; i < larger_size + 1; i++){
            if(b_clone[i] == 0)
                b_clone[i] = 1;
            else if(b_clone[i] == 1)
                b_clone[i] = 0;
        }
        
        // Create BinaryInteger object with b_clone and add to a to get signed_diff
        BinaryInteger b_neg(b_clone, 0);
        BinaryInteger signed_diff = a + b_neg;
        
        // If there is a carried-over bit, add one to the result (this also means signed_diff is positive)
        if((signed_diff.getVec()).size() > larger_size + 1){
            BinaryInteger one(1);
            signed_diff = signed_diff + one;
            
            // Take away the carried-over bit and assign result to diff
            vector<bool> no_carry_bit = signed_diff.getVec();
            no_carry_bit.erase(no_carry_bit.begin());
            
            diff = BinaryInteger(no_carry_bit, 0);
        }
        
        // Otherwise, signed_diff is negative and convert back to regular form
        else{
            vector<bool> no_sign = signed_diff.getVec();
            no_sign.erase(no_sign.begin());
            
            diff = ~(BinaryInteger(no_sign, 0));
        }
    }
    
    // Remove any extra zeros and return object
    diff.CleanUp();
    return diff;
}

/** & operator definition that performs bit-wise AND operation to two BinaryInteger objects
 @param a BinaryInteger object left side
 @param b BinaryInteger object right side
 @return c BinaryInteger object that represents a&b
 */
BinaryInteger operator& (BinaryInteger a, BinaryInteger b){
    int smaller_size;
    if(a.b.size() < b.b.size())
        smaller_size = static_cast<int>(a.b.size());
    else
        smaller_size = static_cast<int>(b.b.size());
    
    // Create aND vector with the size of smaller vector
    vector<bool> aND(smaller_size, 0);
    
    // Sets appropriate sign
    bool sign;
    if(a.s == 1 && b.s == 1)
        sign = 1;
    else
        sign = 0;
    
    // Performs a&b operation and stores in vector aND
    for(int i = 0; i < smaller_size; i++){
        if(a.b.back() == 1 && b.b.back() == 1)
            aND[smaller_size - 1 - i] = 1;
        a.b.pop_back();
        b.b.pop_back();
    }
    
    // Create BinaryInteger object with vector aND
    BinaryInteger c(aND, sign);
    
    // Remove any extra 0s and signs and return object
    c.CleanUp();
    return c;
}

/** | operator definition that performs bit-wise OR operation to two BinaryInteger objects
 @param a BinaryInteger object left side
 @param b BinaryInteger object right side
 @return c BinaryInteger object that represents a|b
 */
BinaryInteger operator| (BinaryInteger a, BinaryInteger b){
    int smaller_size;
    int larger_size;
    vector<bool> larger_vector;
    if(a.b.size() < b.b.size()){
        smaller_size = static_cast<int>(a.b.size());
        larger_size = static_cast<int>(b.b.size());
        larger_vector = b.b;
    }
    else{
        smaller_size = static_cast<int>(b.b.size());
        larger_size = static_cast<int>(a.b.size());
        larger_vector = a.b;
    }
    
    // Create oR vector with the size of the larger vector
    vector<bool> oR(larger_size, 0);
    
    // Sets appropriate sign
    bool sign;
    if(a.s == 1 || b.s == 1)
        sign = 1;
    else
        sign = 0;
    
    // Performs | operation and stores in oR vector starting from the right side to the left side of the smaller vector
    for(int i = 0; i < smaller_size; i++){
        if(a.b.back() == 1 || b.b.back() == 1)
            oR[larger_size - 1 - i] = 1;
        a.b.pop_back();
        b.b.pop_back();
    }
    
    // Fills in the remaining elements with the larger vector
    for(int i = 0; i < larger_size - smaller_size; i++)
        oR[i] = larger_vector[i];
    
    // Create BinaryInteger object with vector oR
    BinaryInteger c(oR, sign);
    
    // Remove any extra 0s and sign and return object
    c.CleanUp();
    return c;
}

/** ^ operator definition that performs bit-wise XOR operation to two BinaryInteger objects
 @param a BinaryInteger object left side
 @param b BinaryInteger object right side
 @return c BinaryInteger object that represents a^b
 */
BinaryInteger operator^ (BinaryInteger a, BinaryInteger b){
    int smaller_size;
    int larger_size;
    vector<bool> larger_vector;
    if(a.b.size() < b.b.size()){
        smaller_size = static_cast<int>(a.b.size());
        larger_size = static_cast<int>(b.b.size());
        larger_vector = b.b;
    }
    else{
        smaller_size = static_cast<int>(b.b.size());
        larger_size = static_cast<int>(a.b.size());
        larger_vector = a.b;
    }
    
    // Create xOR vector with the size of the larger vector
    vector<bool> xOR(larger_size, 0);
    
    // Sets appropriate sign
    bool sign;
    if(a.s != b.s)
        sign = 1;
    else
        sign = 0;
    
    // Performs ^ operation and stores in xOR vector starting from the right side to the left side of the smaller vector
    for(int i = 0; i < smaller_size; i++){
        if(a.b.back() == 1 && b.b.back() == 0)
            xOR[larger_size - 1 - i] = 1;
        else if(a.b.back() == 0 && b.b.back() == 1)
            xOR[larger_size - 1 - i] = 1;
        a.b.pop_back();
        b.b.pop_back();
    }
    
    // Fills in the remaining elements with the larger vector
    for(int i = 0; i < larger_size - smaller_size; i++)
        xOR[i] = larger_vector[i];
    
    // Create BinaryInteger object with vector xOR
    BinaryInteger c(xOR, sign);
    
    // Remove any extra 0s and sign and return object
    c.CleanUp();
    return c;
}

/** ~ operator definition that performs bit-wise negation to a BinaryInteger object
 @param a BinaryInteger object to be negated
 @return c BinaryInterger object that represents ~a
 */
BinaryInteger operator~ (BinaryInteger a){
    int size = static_cast<int>(a.b.size());
    
    // Create negation vector with size of a's vector
    vector<bool> negation(size);
    
    // Sets appropriate sign
    bool sign;
    if(a.s == 1)
        sign = 0;
    else if(a.s == 0)
        sign = 1;
    
    // Performs ~ operation and stores in negation vector
    for(int i = 0; i < size; i++){
        if(a.b[i] == 0)
            negation[i] = 1;
        else if(a.b[i] == 1)
            negation[i] = 0;
    }
    
    // Create BinaryInteger object with negation vector
    BinaryInteger c(negation, sign);
    
    // Remove any extra 0s and sign and return object
    c.CleanUp();
    return c;
}

/** output stream << operator definition that outputs the integer value of the binary vector
 @param out Ostream object out
 @param a BinaryInteger to be outputted as integer value
 @return out Containing integer value of a
 */
ostream& operator<< (ostream& out, const BinaryInteger& a){
    
    // Get integer representation of a and store it in variable n
    int n = 0;
    int size = static_cast<int>(a.b.size());
    
    for(int i = 0; i < size; i++)
        n += pow(2.0, size - 1 - i) * a.b[i];
    
    if(a.s == 1)
        n *= -1;
    
    // Outputs appropriate sign to out stream
    if(n < 0){
        out << "-";
        n *= -1;
    }
    
    // Outputs integer information to out stream and returns out
    out << n;
    return out;
}

/** input stream >> operator definition that reads an integer value from an input stream and stores that information to BinaryInteger a
 @param in Input stream
 @param a BinaryInteger to be inputted to
 @return in
 */
istream& operator>> (istream& in, BinaryInteger& a){
    int n;
    in >> n;
    
    // Sets read-in information to a
    a = BinaryInteger(n);
    return in;
}
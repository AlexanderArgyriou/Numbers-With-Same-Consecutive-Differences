class Solution 
{
    private:
        inline void Digitize( std::string &d, int num ) const noexcept
        {
            if( num < 10 )
                d += ( num + '0' );
            else
            {
                d +=  ( (num % 10) + '0' );
                Digitize( d, num / 10 ); 
            }   // else
        }   // Digitize
    
        inline int NumOfDigs( int Num ) const noexcept
        {
            if( Num < 10 )
                return 1;
            else
                return 1 + NumOfDigs( Num / 10 );
        }   // NumOfDigs
    
        inline void CheckNumber( std::string &d, std::vector<std::string> &result, int k ) const noexcept
        {
            for( int i = 0; i < d.size() - 1; ++i )
            {   
                if( std::abs( (d[i] - '0') - (d[i + 1] - '0') ) != k )
                {
                    d.clear();
                    return;
                }   // if
            }   // CheckNumber
            result.push_back( std::move(d) );
        }   // CheckNumber
    
        inline bool ValidNum( std::string S, int k ) const noexcept
        {
            for( int i = 0; i < S.size() - 1; ++i )
                if( std::abs( (S[i] - '0') - (S[i + 1] - '0') ) != k )
                    return false;
            return true;
        }   // ValidNum
    
    public:
        inline std::vector<int> numsSameConsecDiff( int N, int K ) const noexcept
        {
            std::vector<int> res;
            std::vector<int> nums{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            std::vector<std::string> OneDigSol { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
            std::vector<std::string> TwoDigSol;
            std::vector<std::string> StringRes;
            std::string Digits;
            std::size_t sz;
            
            // N < 2
            if( N == 1 )
                return nums;
        
            // N >= 2
            int start = 10;
            for( int i = 0; i < 90; ++i )
            {
                Digitize( Digits, start++ );
                std::reverse( Digits.begin(), Digits.end() );
                CheckNumber( Digits, TwoDigSol, K );
            }   // for
        
            if( N == 2 )
            {
                for( auto &C : TwoDigSol )
                    res.push_back( stoi(C,&sz) );
                return res;
            }   // if
            else
            {
                std::vector<std::string> ZeroStart;
                for( int i = 1; i <= 9; ++i )
                {
                    std::string s = "0" + to_string(i);
                    ZeroStart.push_back( move(s) );
                }   // for
                
                if( N % 2 == 0)
                {
                    StringRes = TwoDigSol;
                    for( int Numbers = 0; Numbers < N / 2 - 1; ++Numbers )
                    {
                        int len = StringRes.size();
                        for( int i = 0; i < len; ++i )
                        {
                            std::string Digits1;
                            Digitize(Digits1, stoi(StringRes[i], &sz));
                            std::reverse( Digits1.begin(), Digits1.end() );
                            for( int j = 0; j < TwoDigSol.size(); ++j)
                            {
                                std::string Digits2;
                                Digitize( Digits2, stoi(TwoDigSol[j], &sz) );
                                std::reverse( Digits2.begin(), Digits2.end() );
                        
                                if(std::abs((Digits1[Digits1.length() - 1] - '0') - (Digits2[0] - '0'))==K)
                                    StringRes.push_back(Digits1 + Digits2);
                            }   // for
                    
                            for( int i = 0; i < ZeroStart.size(); ++i )
                                if( ValidNum(Digits1 + ZeroStart[i], K) )
                                    StringRes.push_back(Digits1 + ZeroStart[i]);
                        }   // for
                    }   // for
                
                    for(int i = 0; i < StringRes.size(); ++i)
                        if ( NumOfDigs( stoi(StringRes[i], &sz) ) == N )
                            res.push_back( stoi(StringRes[i], &sz) );   
                }   // if
                else
                {
                    StringRes = OneDigSol;
                    for(int Numbers = 0; Numbers < N - 1; ++Numbers)
                    {
                        int len = StringRes.size();
                        for( int i = 0; i < len; ++i )
                        {
                            std::string Digits1;
                            Digitize(Digits1, stoi(StringRes[i], &sz));
                            std::reverse( Digits1.begin(), Digits1.end() );
                            for( int j = 0; j < OneDigSol.size(); ++j)
                            {
                                std::string Digits2;
                                Digitize(Digits2, stoi(OneDigSol[j], &sz));
                                std::reverse( Digits2.begin(), Digits2.end() );
                
                                if(std::abs((Digits1[Digits1.length() - 1] - '0') - (Digits2[0] - '0'))==K)
                                    StringRes.push_back(Digits1 + Digits2);
                            }   // for
                        
                            if( ValidNum(Digits1 + "0", K) )
                                StringRes.push_back(Digits1 + "0");
                        }   // for
                    }   // for

                    for(int i = StringRes.size() - 1;  i >= 0; --i)
                        if ( NumOfDigs( stoi(StringRes[i], &sz) ) == N )
                            res.push_back( stoi(StringRes[i], &sz) );      
                }   //else
            }   // else
        return res;
    }   //  numsSameConsecDiff
};  // Solution

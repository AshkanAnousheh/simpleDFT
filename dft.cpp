#include <cmath>
#include <vector>
#include "matplotlibcpp.h"
#include <complex>
namespace plt = matplotlibcpp;

class DFT
{
    using dft_t = std::vector<std::complex<float>>;
    dft_t inp_, out_;
    size_t N;
    size_t M;

public:
    DFT( size_t N ) : N( N )
    {
        if ( N % 2 )
            M = N / 2;
        else
            M = ( N / 2 ) + 1;
        inp_.resize( N );
        out_.resize( M );
    }
    void load( dft_t& data );
    DFT& exec();
    std::vector<float> mag();
    std::vector<float> real();
    std::vector<float> imag();
    std::vector<float> phase();
};
void DFT::load( dft_t& data )
{
    // inp_.clear();
    if ( inp_.size() >= data.size() )
        {
            for ( size_t i = 0; i < N; ++i )
                {
                    inp_[ i ].real( data[ i ].real() );
                    inp_[ i ].imag( data[ i ].imag() );
                }
        }
}
DFT& DFT::exec()
{
    float real_part;
    float imag_part;
    out_.clear();
    for ( size_t m = 0; m < M; m++ )
        {
            real_part = 0.0f;
            imag_part = 0.0f;
            for ( size_t n = 0; n < N; n++ )
                {
                    real_part += ( std::cos( 2.0f * M_PI * n * m / N )
                                   * inp_[ n ].real() );
                    imag_part += ( std::sin( 2.0f * M_PI * n * m / N )
                                   * inp_[ n ].real() );
                }
            out_[ m ].real( real_part );
            out_[ m ].imag( imag_part );
        }
    return *this;
}
std::vector<float> DFT::mag()
{
    std::vector<float> res( M );
    for ( size_t i = 0; i < M; ++i )
        {
            res[ i ]
                = std::sqrt( out_[ i ].real() * out_[ i ].real()
                             + out_[ i ].imag() * out_[ i ].imag() );
        }
    return res;
}
int main()
{
    uint32_t fs, n, freq, N, M;
    N    = 250;
    freq = 1e3;
    fs   = 10e3;
    float angle;
    std::vector<int32_t> f_axis;
    std::vector<std::complex<float>> inp_signal( N );

    for ( size_t n = 0; n < N; n++ )
        {
            angle = 2.0f * M_PI * freq * n / fs;
            inp_signal[ n ].real( std::sin( angle ) );
        }

    DFT dft( N );
    dft.load( inp_signal );
    auto out = dft.exec().mag();
    M        = out.size();
    f_axis.resize( M );
    for ( size_t n = 0; n < M; ++n )
        f_axis[ n ] = n * fs / N;

    plt::plot( f_axis, out );
    plt::show();
    return 0;
}

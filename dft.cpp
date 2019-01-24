#include <cmath>
#include <vector>
#include "matplotlibcpp.h"
#include <complex>
#include "signal_generator.h"

namespace plt = matplotlibcpp;

class DFT
{
    using dft_t = std::vector<std::complex<float>>;
    dft_t inp_, out_;
    size_t N, Fs;
    size_t M;

public:
    DFT( size_t N, size_t fs ) : N( N ), Fs( fs )
    {
        if ( N % 2 )
            M = N / 2;
        else
            M = ( N / 2 ) + 1;
        inp_.resize( N );
        out_.resize( M );
    }
    void load( dft_t& data );
    void load( std::vector<float>& data );
    std::vector<float> get_freq_axis();
    DFT& exec();
    std::vector<float> mag();
    std::vector<float> real();
    std::vector<float> imag();
    std::vector<float> phase();
};

std::vector<float> DFT::get_freq_axis()
{
    std::vector<float> f_axis( M );
    for ( size_t n = 0; n < M; ++n )
        f_axis[ n ] = n * Fs / N;
    return f_axis;
}

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

void DFT::load( std::vector<float>& data )
{
    // inp_.clear();
    if ( inp_.size() >= data.size() )
        {
            for ( size_t i = 0; i < N; ++i )
                {
                    inp_[ i ].real( data[ i ] );
                    inp_[ i ].imag( 0.0f );
                }
        }
}

DFT& DFT::exec()
{
    float real_part;
    float imag_part;
    float angle;
    out_.clear();
    for ( size_t m = 0; m < M; m++ )
        {
            real_part = 0.0f;
            imag_part = 0.0f;
            angle     = 0.0f;
            for ( size_t n = 0; n < N; n++ )
                {
                    angle = 2.0f * M_PI * n * m / N;
                    real_part
                        += ( std::cos( angle ) * inp_[ n ].real() )
                        + ( std::sin( angle ) * inp_[ n ].imag() );
                    imag_part
                        += ( std::cos( angle ) * inp_[ n ].imag() )
                        - ( std::sin( angle ) * inp_[ n ].real() );
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
        res[ i ] = std::abs( out_[ i ] );
    return res;
}

std::vector<float> DFT::phase()
{
    std::vector<float> res( M );

    for ( size_t i = 0; i < M; ++i )
        res[ i ] = std::arg( out_[ i ] ) * 180 / M_PI;
    return res;
}

std::vector<float> DFT::real()
{
    std::vector<float> res( M );

    for ( size_t i = 0; i < M; ++i )
        res[ i ] = out_[ i ].real();
    return res;
}

std::vector<float> DFT::imag()
{
    std::vector<float> res( M );

    for ( size_t i = 0; i < M; ++i )
        res[ i ] = out_[ i ].imag();
    return res;
}
int main()
{
    uint32_t M, N, fs, freq;
    fs = 8e3;
    N  = 8;

    SignalGenerator<> sin_1k( 1e3, N, fs );
    auto sig1 = sin_1k.sin();

    SignalGenerator<> sin_2k( 2e3, N, fs );
    // sin_2k.change_phase( M_PI / 2 );
    auto sig2 = sin_2k.sin();

    auto sig = sin_1k + sin_2k;

    DFT dft( N, fs );
    dft.load( sig );

    auto out    = dft.exec().phase();
    auto f_axis = dft.get_freq_axis();

    plt::stem( f_axis, out );
    plt::grid( true );
    plt::show();
    return 0;
}

#pragma once
#include <cmath>
#include <vector>

template <typename T = float>
class SignalGenerator
{
    size_t sampling_freq_;

    size_t signal_freq_;
    float signal_phase_;
    size_t singal_length_;
    float signal_scale_;
    std::vector<T> signal_;

public:
    SignalGenerator( float A = 1.0f, size_t freq = 1e3,
                     size_t len = 250, size_t fs = 10e3 ) :
        signal_freq_( freq ),
        signal_scale_( A ), signal_phase_( 0.0f ),
        singal_length_( len ), sampling_freq_( fs )
    {
        signal_.resize( len );
    }

    /* getters and setters */
    std::vector<T> get_signal() const { return this->signal_; };
    T get_freq() const { return signal_freq_; }
    void change_phase_to( float ph ) { signal_phase_ = ph; }
    void change_scale_to( float a ) { signal_scale_ = a; }
    void change_freq_to( size_t fr ) { signal_freq_ = fr; }

    /* signals deceleration */
    std::vector<T> sin();
    std::vector<T> cos();

    /* Operator overloading in order to signal manipulation */
};

// template <typename T>
const std::vector<float> operator+( const std::vector<float>& sgl,
                                    const std::vector<float>& sgr )
{
    std::vector<float> res( sgr.size() );
    for ( size_t i = 0; i < sgr.size(); i++ )
        {
            res[ i ] = sgl[ i ] + sgr[ i ];
        }
    return res;
}

const std::vector<float> operator*( const std::vector<float>& sgl,
                                    const std::vector<float>& sgr )
{
    std::vector<float> res( sgr.size() );
    for ( size_t i = 0; i < sgr.size(); i++ )
        {
            res[ i ] = sgl[ i ] * sgr[ i ];
        }
    return res;
}

const std::vector<float> operator*( const float& scale,
                                    const std::vector<float>& sgr )
{
    std::vector<float> res( sgr.size() );
    for ( size_t i = 0; i < sgr.size(); i++ )
        {
            res[ i ] = scale * sgr[ i ];
        }
    return res;
}

template <typename T>
std::vector<T> SignalGenerator<T>::sin()
{
    float angle;
    for ( size_t n = 0; n < singal_length_; n++ )
        {
            angle = 2.0f * M_PI * signal_freq_ * n / sampling_freq_;
            signal_[ n ]
                = signal_scale_ * std::sin( angle + signal_phase_ );
        }
    return signal_;
}

template <typename T>
std::vector<T> SignalGenerator<T>::cos()
{
    float angle;
    for ( size_t n = 0; n < singal_length_; n++ )
        {
            angle = 2.0f * M_PI * signal_freq_ * n / sampling_freq_;
            signal_[ n ]
                = signal_scale_ * std::cos( angle + signal_phase_ );
        }
    return signal_;
}

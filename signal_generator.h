#pragma once
#include <cmath>
#include <vector>

template <typename T = float>
class SignalGenerator
{
    size_t sampling_freq_;
    size_t signal_freq_;
    int32_t signal_phase_;
    size_t singal_length_;
    std::vector<T> latest_signal;

public:
    SignalGenerator( size_t freq = 1e3, size_t fs = 10e3,
                     size_t len = 250 ) :
        signal_freq_( freq ),
        signal_phase_( 0 ), singal_length_( len ),
        sampling_freq_( fs )
    {
        latest_signal.resize( len );
    }
    std::vector<T> sin();
    std::vector<T> cos();
    void change_phase( size_t ph ) { signal_phase_ = ph; }
    T get_freq() const { return signal_freq_; }
    std::vector<T> operator*( const SignalGenerator<T>& sg );
    std::vector<T> operator+( const SignalGenerator<T>& sg );
    std::vector<T> operator-( const SignalGenerator<T>& sg );
};

template <typename T>
std::vector<T> SignalGenerator<T>::
operator*( const SignalGenerator<T>& sg )
{
    std::vector<float> res( singal_length_ );
    for ( size_t i = 0; i < singal_length_; i++ )
        {
            res[ i ]
                = this->latest_signal[ i ] * sg.latest_signal[ i ];
        }
    return res;
}

template <typename T>
std::vector<T> SignalGenerator<T>::
operator+( const SignalGenerator<T>& sg )
{
    std::vector<float> res( singal_length_ );
    for ( size_t i = 0; i < singal_length_; i++ )
        {
            res[ i ]
                = this->latest_signal[ i ] + sg.latest_signal[ i ];
        }
    return res;
}

template <typename T>
std::vector<T> SignalGenerator<T>::
operator-( const SignalGenerator<T>& sg )
{
    std::vector<float> res( singal_length_ );
    for ( size_t i = 0; i < singal_length_; i++ )
        {
            res[ i ]
                = this->latest_signal[ i ] - sg.latest_signal[ i ];
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
            latest_signal[ n ] = std::sin( angle + signal_phase_ );
        }
    return latest_signal;
}

template <typename T>
std::vector<T> SignalGenerator<T>::cos()
{
    float angle;
    for ( size_t n = 0; n < singal_length_; n++ )
        {
            angle = 2.0f * M_PI * signal_freq_ * n / sampling_freq_;
            latest_signal[ n ] = std::cos( angle + signal_phase_ );
        }
    return latest_signal;
}

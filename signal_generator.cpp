#include "signal_generator.h"

template <typename T>
SignalGenerator<T>& SignalGenerator<T>::
operator*( const SignalGenerator<T>& sg )
{
    size_t freq_ = this->signal_freq_ * sg.signal_freq_;
    SignalGenerator<T> tmp( freq_, this->sampling_freq_,
                            this->singal_length_ );
    return *tmp;
}

template <typename T>
SignalGenerator<T>& SignalGenerator<T>::
operator+( const SignalGenerator<T>& sg )
{
    size_t freq_ = this->signal_freq_ + sg.signal_freq_;
    SignalGenerator<T> tmp( freq_, this->sampling_freq_,
                            this->singal_length_ );
    return *tmp;
}

template <typename T>
std::vector<T> SignalGenerator<T>::sin()
{
    float angle;
    for ( size_t n = 0; n < singal_length_; n++ )
        {
            angle = 2.0f * M_PI * signal_freq_ * n / sampling_freq_;
            latest_signal[ n ] = std::sin( angle );
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
            latest_signal[ n ] = std::cos( angle );
        }
    return latest_signal;
}

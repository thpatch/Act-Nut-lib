#ifndef EXPORTS_HPP_
# define EXPORTS_HPP_

# include	<act/File.hpp>
# include	<nut/Stream.hpp>

extern "C" {

Act::File*	read_act_from_bytes(const uint8_t* buf, size_t buf_size);
Nut::Stream*	read_nut_from_bytes(const uint8_t* buf, size_t buf_size);

}

#endif /* !EXPORTS_HPP_ */

#ifndef UTILS_H_
# define UTILS_H_

# include	<stdint.h>

void		readBytes(const uint8_t*& buf, uint8_t* out, int n);
uint32_t	readInt(const uint8_t*& buf);
void		checkTag(const uint8_t*& buf, uint32_t iTag);

#endif /* !UTILS_H_ */

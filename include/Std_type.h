#ifndef STDTYPES_H_
#define STDTYPES_H_
typedef signed char 	     s8;
typedef signed short  	     s16;
typedef signed long 	     s32;
typedef unsigned char 		 u8;
typedef unsigned short int   u16;
typedef unsigned long int 	 u32;

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
#define CLR_BIT(REG,BIT) (REG&=(~(1<<BIT)))
#define TOG_BIT(REG,BIT) (REG^=(1<<BIT))
#define GET_BIT(REG,BIT) (((REG>>BIT)&1))

#endif /* STDTYPES_H_ */

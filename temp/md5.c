/*
 * MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm
 */
#include <stdio.h>
#include <string.h>

void	Data(const uchar *data, int len, uchar digest[16]);
char	*HexString(const char *data, int len, char *buf);

static	void	Transform_64(const uchar x[64]);
static	void	Transform_16(const ulong x[16]);
static	void	Encode(uchar *output, const ulong *input, int len);
static	void	Decode(ulong *output, const uchar *input, int len);
static	void	Init(void);
static	void	Update(const uchar *input, int inputLen);
static	void	Final(uchar digest[16]);

ulong	state[4];	/* state (ABCD) */
ulong	count[2];	/* number of bits, modulo 2^64 (lsb first) */
uchar	buffer[64];	/* input buffer */

	/** F, G, H and I are basic MD5 functions. */
static	ulong	F(ulong x, ulong y, ulong z) {
		return	(((x) & (y)) | ((~x) & (z)));
	}
static	ulong	G(ulong x, ulong y, ulong z) {
		return	(((x) & (z)) | ((y) & (~z)));
	}
static	ulong	H(ulong x, ulong y, ulong z) {
		return	((x) ^ (y) ^ (z));
	}
static	ulong	I(ulong x, ulong y, ulong z) {
		return	((y) ^ ((x) | (~z)));
	}
	/** ROTATE_LEFT rotates x left n bits. */
static	ulong	ROTATE_LEFT(ulong x, int n) {
		return	(((x) << (n)) | ((x) >> (32-(n))));
	}
	/** FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
	 *  Rotation is separate from addition to prevent recomputation.
	 */
/*
static	void	FF(ulong &a, ulong b, ulong c, ulong d, ulong x, int s, ulong ac) {
		(a) += F ((b), (c), (d)) + (x) + (ac);
		(a) = ROTATE_LEFT ((a), (s));
		(a) += (b);
	}
static	void	GG(ulong &a, ulong b, ulong c, ulong d, ulong x, int s, ulong ac) {
		(a) += G ((b), (c), (d)) + (x) + (ac);
		(a) = ROTATE_LEFT ((a), (s));
		(a) += (b);
}
static	void	HH(ulong &a, ulong b, ulong c, ulong d, ulong x, int s, ulong ac) {
		(a) += H ((b), (c), (d)) + (x) + (ac);
		(a) = ROTATE_LEFT ((a), (s));
		(a) += (b);
	}
static	void	II(ulong &a, ulong b, ulong c, ulong d, ulong x, int s, ulong ac) {
		(a) += I ((b), (c), (d)) + (x) + (ac);
		(a) = ROTATE_LEFT ((a), (s));
		(a) += (b);
	}
*/
#define FF(a, b, c, d, x, s, ac) \
		(a) += F ((b), (c), (d)) + (x) + (ac);\
		(a) = ROTATE_LEFT ((a), (s));\
		(a) += (b);
        
#define GG(a, b, c, d, x, s, ac) \
		(a) += G ((b), (c), (d)) + (x) + (ac);\
		(a) = ROTATE_LEFT ((a), (s));\
		(a) += (b);
        
#define HH(a, b, c, d, x, s, ac) \
		(a) += H ((b), (c), (d)) + (x) + (ac);\
		(a) = ROTATE_LEFT ((a), (s));\
		(a) += (b);
        
#define II(a, b, c, d, x, s, ac) \
		(a) += I ((b), (c), (d)) + (x) + (ac);\
		(a) = ROTATE_LEFT ((a), (s));\
		(a) += (b);


/*
 * Constants for MD5Transform routine.
 */
const	int	S[4][4] = {
	{ 7, 12, 17, 22,},
	{ 5,  9, 14, 20,},
	{ 4, 11, 16, 23,},
	{ 6, 10, 15, 21,},
};
const	ulong	ac[64] = {
	0xd76aa478l, 0xe8c7b756l, 0x242070dbl, 0xc1bdceeel,
	0xf57c0fafl, 0x4787c62al, 0xa8304613l, 0xfd469501l,
	0x698098d8l, 0x8b44f7afl, 0xffff5bb1l, 0x895cd7bel,
	0x6b901122l, 0xfd987193l, 0xa679438el, 0x49b40821l,
	0xf61e2562l, 0xc040b340l, 0x265e5a51l, 0xe9b6c7aal,
	0xd62f105dl, 0x02441453l, 0xd8a1e681l, 0xe7d3fbc8l,
	0x21e1cde6l, 0xc33707d6l, 0xf4d50d87l, 0x455a14edl,
	0xa9e3e905l, 0xfcefa3f8l, 0x676f02d9l, 0x8d2a4c8al,
	0xfffa3942l, 0x8771f681l, 0x6d9d6122l, 0xfde5380cl,
	0xa4beea44l, 0x4bdecfa9l, 0xf6bb4b60l, 0xbebfbc70l,
	0x289b7ec6l, 0xeaa127fal, 0xd4ef3085l, 0x04881d05l,
	0xd9d4d039l, 0xe6db99e5l, 0x1fa27cf8l, 0xc4ac5665l,
	0xf4292244l, 0x432aff97l, 0xab9423a7l, 0xfc93a039l,
	0x655b59c3l, 0x8f0ccc92l, 0xffeff47dl, 0x85845dd1l,
	0x6fa87e4fl, 0xfe2ce6e0l, 0xa3014314l, 0x4e0811a1l,
	0xf7537e82l, 0xbd3af235l, 0x2ad7d2bbl, 0xeb86d391l,
};

const	uchar	PADDING[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * Encodes input (ulong) into output (uchar). Assumes len is a
 * multiple of 4.
 */
void
Encode(uchar *output, const ulong *input, int len)
{
	int    i, j;

	//assert((len % 4) == 0);

	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (uchar) (input[i] & 0xff);
		output[j + 1] = (uchar) ((input[i] >> 8) & 0xff);
		output[j + 2] = (uchar) ((input[i] >> 16) & 0xff);
		output[j + 3] = (uchar) ((input[i] >> 24) & 0xff);
	}
}

/*
 * Decodes input (uchar) into output (ulong). Assumes len is a
 * multiple of 4.
 */
void
Decode(ulong *output, const uchar *input, int len)
{
	int    i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((ulong) input[j]) | (((ulong) input[j + 1]) << 8) |
			(((ulong) input[j + 2]) << 16) | (((ulong) input[j + 3]) << 24);
}

/*
 * MD5 basic transformation. Transforms state based on block.
 */
void
Transform_64(const uchar block[64])
{
	ulong	x[16];
	Decode(x, block, 64);
	Transform_16(x);

	/** Zeroize sensitive information. */
	//memset((uchar *) x, 0, sizeof(x));
}
void
Transform_16(const ulong x[16])
{
	ulong	a = state[0], b = state[1],
		c = state[2], d = state[3];

	/* Round 1 */
	FF(a, b, c, d, x[ 0], S[0][0], 0xd76aa478l);	/* 1 */
	FF(d, a, b, c, x[ 1], S[0][1], 0xe8c7b756l);	/* 2 */
	FF(c, d, a, b, x[ 2], S[0][2], 0x242070dbl);	/* 3 */
	FF(b, c, d, a, x[ 3], S[0][3], 0xc1bdceeel);	/* 4 */
	FF(a, b, c, d, x[ 4], S[0][0], 0xf57c0fafl);	/* 5 */
	FF(d, a, b, c, x[ 5], S[0][1], 0x4787c62al);	/* 6 */
	FF(c, d, a, b, x[ 6], S[0][2], 0xa8304613l);	/* 7 */
	FF(b, c, d, a, x[ 7], S[0][3], 0xfd469501l);	/* 8 */
	FF(a, b, c, d, x[ 8], S[0][0], 0x698098d8l);	/* 9 */
	FF(d, a, b, c, x[ 9], S[0][1], 0x8b44f7afl);	/* 10 */
	FF(c, d, a, b, x[10], S[0][2], 0xffff5bb1l);	/* 11 */
	FF(b, c, d, a, x[11], S[0][3], 0x895cd7bel);	/* 12 */
	FF(a, b, c, d, x[12], S[0][0], 0x6b901122l);	/* 13 */
	FF(d, a, b, c, x[13], S[0][1], 0xfd987193l);	/* 14 */
	FF(c, d, a, b, x[14], S[0][2], 0xa679438el);	/* 15 */
	FF(b, c, d, a, x[15], S[0][3], 0x49b40821l);	/* 16 */

	/* Round 2 */
	GG(a, b, c, d, x[ 1], S[1][0], 0xf61e2562l);	/* 17 */
	GG(d, a, b, c, x[ 6], S[1][1], 0xc040b340l);	/* 18 */
	GG(c, d, a, b, x[11], S[1][2], 0x265e5a51l);	/* 19 */
	GG(b, c, d, a, x[ 0], S[1][3], 0xe9b6c7aal);	/* 20 */
	GG(a, b, c, d, x[ 5], S[1][0], 0xd62f105dl);	/* 21 */
	GG(d, a, b, c, x[10], S[1][1], 0x02441453l);	/* 22 */
	GG(c, d, a, b, x[15], S[1][2], 0xd8a1e681l);	/* 23 */
	GG(b, c, d, a, x[ 4], S[1][3], 0xe7d3fbc8l);	/* 24 */
	GG(a, b, c, d, x[ 9], S[1][0], 0x21e1cde6l);	/* 25 */
	GG(d, a, b, c, x[14], S[1][1], 0xc33707d6l);	/* 26 */
	GG(c, d, a, b, x[ 3], S[1][2], 0xf4d50d87l);	/* 27 */
	GG(b, c, d, a, x[ 8], S[1][3], 0x455a14edl);	/* 28 */
	GG(a, b, c, d, x[13], S[1][0], 0xa9e3e905l);	/* 29 */
	GG(d, a, b, c, x[ 2], S[1][1], 0xfcefa3f8l);	/* 30 */
	GG(c, d, a, b, x[ 7], S[1][2], 0x676f02d9l);	/* 31 */
	GG(b, c, d, a, x[12], S[1][3], 0x8d2a4c8al);	/* 32 */

	/* Round 3 */
	HH(a, b, c, d, x[ 5], S[2][0], 0xfffa3942l);	/* 33 */
	HH(d, a, b, c, x[ 8], S[2][1], 0x8771f681l);	/* 34 */
	HH(c, d, a, b, x[11], S[2][2], 0x6d9d6122l);	/* 35 */
	HH(b, c, d, a, x[14], S[2][3], 0xfde5380cl);	/* 36 */
	HH(a, b, c, d, x[ 1], S[2][0], 0xa4beea44l);	/* 37 */
	HH(d, a, b, c, x[ 4], S[2][1], 0x4bdecfa9l);	/* 38 */
	HH(c, d, a, b, x[ 7], S[2][2], 0xf6bb4b60l);	/* 39 */
	HH(b, c, d, a, x[10], S[2][3], 0xbebfbc70l);	/* 40 */
	HH(a, b, c, d, x[13], S[2][0], 0x289b7ec6l);	/* 41 */
	HH(d, a, b, c, x[ 0], S[2][1], 0xeaa127fal);	/* 42 */
	HH(c, d, a, b, x[ 3], S[2][2], 0xd4ef3085l);	/* 43 */
	HH(b, c, d, a, x[ 6], S[2][3], 0x04881d05l);	/* 44 */
	HH(a, b, c, d, x[ 9], S[2][0], 0xd9d4d039l);	/* 45 */
	HH(d, a, b, c, x[12], S[2][1], 0xe6db99e5l);	/* 46 */
	HH(c, d, a, b, x[15], S[2][2], 0x1fa27cf8l);	/* 47 */
	HH(b, c, d, a, x[ 2], S[2][3], 0xc4ac5665l);	/* 48 */

	/* Round 4 */
	II(a, b, c, d, x[ 0], S[3][0], 0xf4292244l);	/* 49 */
	II(d, a, b, c, x[ 7], S[3][1], 0x432aff97l);	/* 50 */
	II(c, d, a, b, x[14], S[3][2], 0xab9423a7l);	/* 51 */
	II(b, c, d, a, x[ 5], S[3][3], 0xfc93a039l);	/* 52 */
	II(a, b, c, d, x[12], S[3][0], 0x655b59c3l);	/* 53 */
	II(d, a, b, c, x[ 3], S[3][1], 0x8f0ccc92l);	/* 54 */
	II(c, d, a, b, x[10], S[3][2], 0xffeff47dl);	/* 55 */
	II(b, c, d, a, x[ 1], S[3][3], 0x85845dd1l);	/* 56 */
	II(a, b, c, d, x[ 8], S[3][0], 0x6fa87e4fl);	/* 57 */
	II(d, a, b, c, x[15], S[3][1], 0xfe2ce6e0l);	/* 58 */
	II(c, d, a, b, x[ 6], S[3][2], 0xa3014314l);	/* 59 */
	II(b, c, d, a, x[13], S[3][3], 0x4e0811a1l);	/* 60 */
	II(a, b, c, d, x[ 4], S[3][0], 0xf7537e82l);	/* 61 */
	II(d, a, b, c, x[11], S[3][1], 0xbd3af235l);	/* 62 */
	II(c, d, a, b, x[ 2], S[3][2], 0x2ad7d2bbl);	/* 63 */
	II(b, c, d, a, x[ 9], S[3][3], 0xeb86d391l);	/* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

}

/**
 * Initializes MD5 context for the start of message digest computation.
 **/
void
Init()
{
	count[0] = count[1] = 0;
	/* Load magic initialization constants.  */
	state[0] = 0x67452301l;
	state[1] = 0xefcdab89l;
	state[2] = 0x98badcfel;
	state[3] = 0x10325476l;
}

/**
 * @input: pointer to data to be fed into MD5 algorithm.
 * @inputLen: size of @input data in bytes.
 *
 * MD5 block update operation. Continues an MD5 message-digest operation,
 * processing another message block, and updating the context.
 **/
void
Update(const uchar *input, int inputLen)
{
	int    i, index, partLen;

	/* Compute number of bytes mod 64 */
	index = (unsigned int) ((count[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((count[0] += ((ulong) inputLen << 3)) < ((ulong) inputLen << 3)) {
		count[1]++;
	}
	count[1] += ((ulong) inputLen >> 29);

	partLen = 64 - index;

	/* Transform as many times as possible.  */
	if (inputLen >= partLen) {
		memcpy(&buffer[index], input, partLen);
		Transform_64(buffer);

		for (i = partLen; i + 63 < inputLen; i += 64) {
			Transform_64(&input[i]);
		}
		index = 0;
	} else {
		i = 0;
	}

	/* Buffer remaining input */
	if ((inputLen - i) != 0) {
		memcpy(&buffer[index], &input[i], inputLen - i);
	}
}

/**
 * @digest: 16-byte buffer to write MD5 checksum.
 *
 * Ends an MD5 message-digest operation, writing the the message
 * digest and zeroing the context.  The context must be initialized
 * with Init() before being used for other MD5 checksum calculations.
 **/
void
Final(uchar digest[16])
{
	uchar   bits[8];
	int	index, padLen;

	/* Save number of bits */
	Encode(bits, count, 8);

	/** Pad out to 56 mod 64. */
	index =(int) ((count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	Update(PADDING, padLen);

	/* Append length (before padding) */
	Update(bits, 8);
	/* Store state in digest */
	Encode(digest, state, 16);

	/** Zeroize sensitive information. */
	//memset((uchar *)this, 0, sizeof(*this));
}



/**
 * @data: pointer to data to be fed into MD5 algorithm.
 * @len: size of @data in bytes.
 * @digest: 16-byte buffer to write MD5 checksum.
 *
 * calculate the MD5 checksum.
 **/
void
Data(const uchar *data, int len, uchar digest[16])
{
	Init();
	Update(data, len);
	Final(digest);
}

char	*
HexString(const char *data, int len, char *buf)
{
	uchar	digest[16];

	Data((const uchar *)data, len, digest);
	char	*p = buf;
	for (int i = 0; i < 16; i++) {
		*p++ = "0123456789abcdef"[digest[i] >> 4];
		*p++ = "0123456789abcdef"[digest[i] & 0x0f];
	}
	*p = 0;

	return	buf;
}

void	test1(void)
{
	char	out[33];

    char *str = "aaabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh";
    //char *str = "abcdefghabcdefg";
    //char *str = "a";

    HexString(str, strlen(str), out);
		//printf("%s\n",	HexString(str, strlen(str), out));

    while(1);
}

int main(int argc, char *argv[])
{
    test1();
    return 0;
}



typedef struct
{
	uint32_t start;	// blockhead
	uint32_t size;
	uint32_t state;
} memorymap_t;
typedef struct
{
	open;
	release;
	read;
	write;
	ioctl;
	uint8_t *memorybank[4];	// blocksize=1024*4=page
	uint32_t bankoffset[4];
} fops_t;	// fileoperations

typedef  struct
{
	Register;
	unregister;
	uint32_t deviceid;
	kobjectstate_t state;
} drivers_t;


typedef struct
{
} nfc_t;

typedef struct
{
} wifi_t;

typedef struct
{
	uint32_t v;
	uint32_t i;
	uint32_t dianliang;
} power_t;

typedef struct
{
	uint32_t v;
	uint32_t i;
	uint32_t sudu;
	uint32_t jiaodu;
	uint32_t jiasudu;
	uint32_t maxsudu;
} motor_t;

typedef struct
{
	uint32_t pinglv;
	uint32_t sudu;
	uint32_t lenth;
} rf_t;

typedef struct
{
} gui_t;

typedef struct
{

} touch_t;



typedef struct
{
	uint32_t systick;
	
} bootloarder_t;

typedef struct
{
	uint32_t systick;
	void (*ProcessSwitch);
	void (*ThreadSwtich)
	void (*JumpToApp);
} app_t;




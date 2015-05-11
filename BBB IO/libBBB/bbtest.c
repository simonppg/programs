/*  BBTEST

Beaglebone Black GPIO-IN GPIO-OUT PWM AIN テストプログラム. 高精度タイマー DMTIMERもおまけ

AIN PWM関係は、Adafruit_BBIOとかを参考にしています。
ご自由に。
*/
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <math.h>

typedef int BEAGLEBONE_GPIO_ENUM;
#define BEAGLEBONE_GPIO_IN   1
#define BEAGLEBONE_GPIO_OUT  0


int g_gpio_mem_fd = -1;
volatile unsigned long* g_gpio_mem_map = (unsigned long*)MAP_FAILED;


#define MMAP_OFFSET 0x44c00000
#define MMAP_SIZE   (0x48ffffff - MMAP_OFFSET)

#define GPIO0_MEM   (0x44e07000 - MMAP_OFFSET)
#define GPIO1_MEM   (0x4804c000 - MMAP_OFFSET)
#define GPIO2_MEM   (0x481ac000 - MMAP_OFFSET)
#define GPIO3_MEM   (0x481ae000 - MMAP_OFFSET)
#define DMTIMER0_MEM (0x44E05000 - MMAP_OFFSET)
#define DMTIMER2_MEM (0x48040000 - MMAP_OFFSET)
#define DMTIMER3_MEM (0x48042000 - MMAP_OFFSET)
#define DMTIMER4_MEM (0x48044000 - MMAP_OFFSET)
#define DMTIMER5_MEM (0x48046000 - MMAP_OFFSET)
#define DMTIMER6_MEM (0x48048000 - MMAP_OFFSET)
#define DMTIMER7_MEM (0x4804A000 - MMAP_OFFSET)

#define GPIO_OE            0x134
#define GPIO_DATAIN        0x138
#define GPIO_DATAOUT       0x13c
#define GPIO_CLEARDATAOUT  0x190
#define GPIO_SETDATAOUT    0x194

#define ARRAY_COUNTOF(arr)	(sizeof(arr)/sizeof(arr[0]))

#define GPIO_MEMORY_TO(gpioNo) (( (gpioNo) / 32) == 0 ? GPIO0_MEM : (( (gpioNo) / 32) == 1 ? GPIO1_MEM : (( (gpioNo) / 32) == 2 ? GPIO2_MEM : GPIO3_MEM )  ) )
#define GPIO_BIT_TO(gpioNo) (1 << (gpioNo)%32)

//inとoutを両方作る
#define GPIO_INDEX_TO(gpioNo) (gpioNo),(GPIO_MEMORY_TO(gpioNo)+GPIO_OE)/4,(GPIO_MEMORY_TO(gpioNo)+GPIO_DATAIN)/4,(GPIO_MEMORY_TO(gpioNo)+GPIO_DATAOUT)/4,GPIO_BIT_TO(gpioNo),~GPIO_BIT_TO(gpioNo)

struct GPIOPIN{
  const char*		portname;
  const char*		auxname;
  int				gpioindex;
  unsigned long		addressINIT;
  unsigned long		addressIN;
  unsigned long		addressOUT;
  unsigned			bitmask;
  unsigned			bitNOTmask;
} ;

const struct GPIOPIN GPIO_PINS[] = {
//portname		auxname				gpioindex/addressIN/addressOUT/bitmask / bitNOTmask
 {"P8_3",		"gpmc_ad6",			GPIO_INDEX_TO(38) }
,{"P8_4",		"gpmc_ad7",			GPIO_INDEX_TO(39) }
,{"P8_5",		"gpmc_ad2",			GPIO_INDEX_TO(34) }
,{"P8_6",		"gpmc_ad3",			GPIO_INDEX_TO(35) }
,{"P8_7",		"gpmc_advn_ale",	GPIO_INDEX_TO(66) }	//TIMER4
,{"P8_8",		"gpmc_oen_ren",		GPIO_INDEX_TO(67) }	//TIMER7
,{"P8_9",		"gpmc_ben0_cle",	GPIO_INDEX_TO(69) }	//TIMER5
,{"P8_10",		"gpmc_wen",			GPIO_INDEX_TO(68) }	//TIMER6
,{"P8_11",		"gpmc_ad13",		GPIO_INDEX_TO(45) }	//GPIO1_13
,{"P8_12",		"gpmc_ad12",		GPIO_INDEX_TO(44) }	//GPIO1_12
,{"P8_13",		"gpmc_ad9",			GPIO_INDEX_TO(23) }	//EHRPWM2B
,{"P8_14",		"gpmc_ad10",		GPIO_INDEX_TO(26) }	//GPIO0_26
,{"P8_15",		"gpmc_ad15",		GPIO_INDEX_TO(47) }	//GPIO1_15
,{"P8_16",		"gpmc_ad14",		GPIO_INDEX_TO(46) }	//GPIO1_14
,{"P8_17",		"gpmc_ad11",		GPIO_INDEX_TO(27) }	//GPIO0_27
,{"P8_18",		"gpmc_clk",			GPIO_INDEX_TO(65) }	//GPIO2_1
,{"P8_19",		"gpmc_ad8",			GPIO_INDEX_TO(22) }	//EHRPWM2A
,{"P8_20",		"gpmc_csn2",		GPIO_INDEX_TO(63) }	//GPIO1_31
,{"P8_21",		"gpmc_csn1",		GPIO_INDEX_TO(62) }	//GPIO1_30
,{"P8_22",		"gpmc_ad5",			GPIO_INDEX_TO(37) }	//GPIO1_5
,{"P8_23",		"gpmc_ad4",			GPIO_INDEX_TO(36) }	//GPIO1_4
,{"P8_24",		"gpmc_ad1",			GPIO_INDEX_TO(33) }	//GPIO1_1
,{"P8_25",		"gpmc_ad0",			GPIO_INDEX_TO(32) }	//GPIO1_0
,{"P8_26",		"gpmc_csn0",		GPIO_INDEX_TO(61) }	//GPIO1_29
,{"P8_27",		"lcd_vsync",		GPIO_INDEX_TO(86) }	//GPIO2_22
,{"P8_28",		"lcd_pclk",			GPIO_INDEX_TO(88) }	//GPIO2_22
,{"P8_29",		"lcd_hsync",		GPIO_INDEX_TO(87) }	//GPIO2_23
,{"P8_30",		"lcd_ac_bias_en",	GPIO_INDEX_TO(89) }	//GPIO2_25
,{"P8_31",		"lcd_data14",		GPIO_INDEX_TO(10) }	//UART5_CTSN
,{"P8_32",		"lcd_data15",		GPIO_INDEX_TO(11) }	//UART5_RTSN
,{"P8_33",		"lcd_data13",		GPIO_INDEX_TO(9)  }	//UART4_RTSN
,{"P8_34",		"lcd_data11",		GPIO_INDEX_TO(81) }	//UART3_RTSN
,{"P8_35",		"lcd_data12",		GPIO_INDEX_TO(8)  }	//UART4_CTSN
,{"P8_36",		"lcd_data10",		GPIO_INDEX_TO(80) }	//UART3_CTSN
,{"P8_37",		"lcd_data8",		GPIO_INDEX_TO(78) }	//UART5_TXD
,{"P8_38",		"lcd_data9",		GPIO_INDEX_TO(79) }	//UART5_RXD
,{"P8_39",		"lcd_data6",		GPIO_INDEX_TO(76) }	//GPIO2_12
,{"P8_40",		"lcd_data7",		GPIO_INDEX_TO(77) }	//GPIO2_13
,{"P8_41",		"lcd_data4",		GPIO_INDEX_TO(74) }	//GPIO2_10
,{"P8_42",		"lcd_data5",		GPIO_INDEX_TO(75) }	//GPIO2_11
,{"P8_43",		"lcd_data2",		GPIO_INDEX_TO(72) }	//GPIO2_8
,{"P8_44",		"lcd_data3",		GPIO_INDEX_TO(73) }	//GPIO2_9
,{"P8_45",		"lcd_data0",		GPIO_INDEX_TO(70) }	//GPIO2_6
,{"P8_46",		"lcd_data1",		GPIO_INDEX_TO(71) }	//GPIO2_7
,{"P9_11",		"gpmc_wait0",		GPIO_INDEX_TO(30) }	//P9_11
,{"P9_12",		"gpmc_ben1",		GPIO_INDEX_TO(60) }	//GPIO1_28
,{"P9_13",		"gpmc_wpn",			GPIO_INDEX_TO(31) }	//UART4_TXD
,{"P9_14",		"gpmc_a2",			GPIO_INDEX_TO(50) }	//EHRPWM1A
,{"P9_15",		"mii1_rxd3",		GPIO_INDEX_TO(48) }	//GPIO1_16
,{"P9_16",		"gpmc_a3",			GPIO_INDEX_TO(51) }	//EHRPWM1B
,{"P9_17",		"spi0_cs0",			GPIO_INDEX_TO(5)  }	//I2C1_SCL
,{"P9_18",		"spi0_d1",			GPIO_INDEX_TO(4)  }	//I2C1_SDA
,{"P9_19",		"uart1_rtsn",		GPIO_INDEX_TO(13) }	//I2C2_SCL
,{"P9_20",		"uart1_ctsn",		GPIO_INDEX_TO(12) }	//I2C2_SDA
,{"P9_21",		"spi0_d0",			GPIO_INDEX_TO(3)  }	//UART2_TXD
,{"P9_22",		"spi0_sclk",		GPIO_INDEX_TO(2)  }	//spi0_sclk
,{"P9_23",		"gpmc_a1",			GPIO_INDEX_TO(49) }	//GPIO1_17
,{"P9_24",		"uart1_txd",		GPIO_INDEX_TO(15) }	//GPIO1_18
,{"P9_25",		"mcasp0_ahclkx",	GPIO_INDEX_TO(117)}	//GPIO3_21
,{"P9_26",		"uart1_rxd",		GPIO_INDEX_TO(14) }	//UART1_RXD
,{"P9_27",		"mcasp0_fsr",		GPIO_INDEX_TO(115)}	//GPIO3_19
,{"P9_28",		"mcasp0_ahclkr",	GPIO_INDEX_TO(113)}	//SPI1_CS0
,{"P9_29",		"mcasp0_fsx",		GPIO_INDEX_TO(111)}	//SPI1_D0
,{"P9_30",		"mcasp0_axr0",		GPIO_INDEX_TO(112)}	//SPI1_D1
,{"P9_31",		"mcasp0_aclkx",		GPIO_INDEX_TO(110)}	//SPI1_SCLK
,{"P9_41",		"xdma_event_intr1",	GPIO_INDEX_TO(20) }	//CLKOUT2
,{"P9_42",		"ecap0_in_pwm0_out",GPIO_INDEX_TO(7)  }	//GPIO0_7
,{"USR0",		"gpmc_a5",			GPIO_INDEX_TO(53) }	//USR0
,{"USR1",		"gpmc_a6",			GPIO_INDEX_TO(54) }	//USR1
,{"USR2",		"gpmc_a7",			GPIO_INDEX_TO(55) }	//USR2
,{"USR3",		"gpmc_a8",			GPIO_INDEX_TO(56) }	//USR3
};

int isExist(const char* filename)
{
	struct stat st;
	return stat(filename ,&st)  == 0;
}


void echoWrite(const char* value , const char* filename) 
{
	FILE *pin;

	if ( (pin  = fopen(filename,"w")) != NULL) {
		fwrite(value , sizeof(char) , strlen(value) , pin);
		fclose(pin);
			printf("filename:%s   value:%s\n",filename,value);
		return;
	}
	printf("failed to filename:%s\n",filename);
	return;
}
void echoWriteInt(int value , const char* filename) 
{
	FILE *pin;

	if ( (pin  = fopen(filename,"w")) != NULL) {
		fprintf(pin,"%d",value);
		fclose(pin);
			printf("filename:%s   value:%d\n",filename,value);
		return;
	}
	printf("failed to filename:%s\n",filename);
	return;
}
int beaglebone_findpath(const char* basepath,const char* findPrefix,char* retPath,unsigned int len)
{
	DIR* handle = opendir(basepath);
	if (!handle)
	{
		return 0;
	}
	struct dirent* ent;
	while(ent = readdir(handle))
	{
		if ( strstr(ent->d_name,findPrefix) )
		{
			snprintf(retPath,len,"%s/%s",basepath,ent->d_name);
			closedir(handle);
			return 1;
		}
	}
	closedir(handle);
	return 0;
}


int beaglebone_slot_install(const char* name)
{
	char bone_capemgr[50];
	char slot[50];
	if (! beaglebone_findpath("/sys/devices", "bone_capemgr",bone_capemgr,sizeof(bone_capemgr)) )
	{
		printf("can not found /sys/devices/bone_capemgr* directory.\n");
		return 0;
	}
	snprintf(slot,sizeof(slot),"%s/slots",bone_capemgr);

	//既にスロットに追加されているか？
	char line[256];
	FILE * fp = fopen(slot,"r+");
	if (!fp)
	{
		printf("can not open %s\n",slot);
		return 0;
	}
	while( fgets(line,sizeof(line),fp) )
	{
		if (strstr(line,name) )
		{
			fclose(fp);
			//既に追加されている
			return 10;
		}
	}
	fclose(fp);

	//追加する.
	fp = fopen(slot,"r+");
	if (!fp)
	{
		printf("can not open %s\n",slot);
		return 0;
	}
	fprintf(fp,"%s",name);
	fclose(fp);
	
	printf("install slot %s !\n",name);
	return 1;
}

int beaglebone_slot_uninstall(const char* name)
{
	char bone_capemgr[50];
	char slot[50];
	if (! beaglebone_findpath("/sys/devices", "bone_capemgr",bone_capemgr,sizeof(bone_capemgr)) )
	{
		printf("can not found /sys/devices/bone_capemgr* directory.\n");
		return 0;
	}
	snprintf(slot,sizeof(slot),"%s/slots",bone_capemgr);

	char line[256];
	FILE * fp = fopen(slot,"r+");
	if (!fp)
	{
		printf("can not open %s\n",slot);
		return 0;
	}
	while( fgets(line,sizeof(line),fp) )
	{
		if (strstr(line,name) )
		{
			//parse number
			char * numerStart = line;
			printf("line %s\n",line);
			for( ; *numerStart ; numerStart++)
			{
				if (*numerStart != ' ') break;
			}
			char * numerEnd = numerStart;
			for( ; *numerEnd ; numerEnd++)
			{
				if (*numerEnd == ':') break;
			}
			if (numerStart == numerEnd || *numerStart == '\0' || *numerEnd == '\0')
			{
				printf("can not parse line: %s\n",line);
				fclose(fp);
				return 0;
			}
			
//			printf("line parse atoi %d\n",atoi(line));
			*numerEnd = '\0';
//			printf("line parse atoi %s\n",numerStart);

			fprintf(fp, "-%s", numerStart);
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);

	return 1;
}

int beaglebone_slot_check(const char* name)
{
	char bone_capemgr[50];
	char slot[50];
	if (! beaglebone_findpath("/sys/devices", "bone_capemgr",bone_capemgr,sizeof(bone_capemgr)) )
	{
		printf("can not found /sys/devices/bone_capemgr* directory.\n");
		return 0;
	}
	snprintf(slot,sizeof(slot),"%s/slots",bone_capemgr);

	char line[256];
	FILE * fp = fopen(slot,"r+");
	if (!fp)
	{
		printf("can not open %s\n",slot);
		return 0;
	}
	while( fgets(line,sizeof(line),fp) )
	{
		if (strstr(line,name) )
		{
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

void beaglebone_clean()
{
	if (g_gpio_mem_fd < 0)
	{
		return ;
	}
	close(g_gpio_mem_fd);
}


//beagleboneを初期化します
int beaglebone_init()
{
	beaglebone_clean();

	g_gpio_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (g_gpio_mem_fd < 0)
	{
		printf("Could not open GPIO memory fd\n");
		return -1;
	}
	
	g_gpio_mem_map = ( unsigned long*) mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE,MAP_SHARED, g_gpio_mem_fd, MMAP_OFFSET);
	if (g_gpio_mem_map == MAP_FAILED) {
		printf ("GPIO Mapping failed\n");
		close(g_gpio_mem_fd);
		return -2;
	}
	return 1;
}

const struct GPIOPIN* beaglebone_gpio_init_for_rawindex(int rawindex,BEAGLEBONE_GPIO_ENUM isIO)
{
	char filename[128];
	const struct GPIOPIN* gpiodef = &GPIO_PINS[rawindex];
///BBBでは不要らしい.
//	sprintf(filename,"/sys/kernel/debug/omap_mux/%s",gpiodef->auxname);
//	echoWrite(isIO ? "37" : "7",filename );
	sprintf(filename,"/sys/class/gpio/export");
	echoWriteInt(gpiodef->gpioindex,filename );

	sprintf(filename,"/sys/class/gpio/gpio%d/direction" , gpiodef->gpioindex);
	echoWrite(isIO ? "in" : "out",filename );

	return gpiodef;
}

const struct GPIOPIN* beaglebone_gpio_init_for_name(const char* name,BEAGLEBONE_GPIO_ENUM isIO)
{
	int i;
	for(i = 0 ; i < ARRAY_COUNTOF(GPIO_PINS) ; i++ )
	{
		if (strcmp(GPIO_PINS[i].portname,name) == 0 )
		{
			printf(" %s --> %d\n",name,i);
			return beaglebone_gpio_init_for_rawindex(i,isIO);
		}
	}
	printf("%s not FOUND!",name);
	
	return NULL;
}

void beaglebone_gpio_clean(const struct GPIOPIN* gpiodef)
{
	if (gpiodef == NULL) return ;
//	char filename[128];
//	sprintf(filename,"/sys/class/gpio/unexport");
//	echoWriteInt( gpiodef->gpioindex,filename );
}

inline int beaglebone_gpio_read(const struct GPIOPIN* gpiodef)
{
	return (g_gpio_mem_map[gpiodef->addressIN] & gpiodef->bitmask) ;
}

inline void beaglebone_gpio_write_on(const struct GPIOPIN* gpiodef)
{
	g_gpio_mem_map[gpiodef->addressOUT] |= gpiodef->bitmask;
}
inline void beaglebone_gpio_write_off(const struct GPIOPIN* gpiodef)
{
	g_gpio_mem_map[gpiodef->addressOUT] &= gpiodef->bitNOTmask;
}

inline void beaglebone_gpio_write(const struct GPIOPIN* gpiodef,int value)
{
	if (value)
	{
		beaglebone_gpio_write_on(gpiodef);
	}
	else 
	{
		beaglebone_gpio_write_off(gpiodef);
	}
}

//高精度の時刻を取得.
inline unsigned long beaglebone_dmtimer_get()
{
//	return g_gpio_mem_map[(DMTIMER2_MEM + 0x3c) / 4] &0x3FFFF; //有効桁が 18bitらしい.
	return g_gpio_mem_map[(DMTIMER2_MEM + 0x3c) / 4] ;//そんなことはない？
}



struct AINPIN{
  const char*		portname;
  const char*		AINname;
  char              filename[50]; //面倒だからメモリで.
} ;
struct AINPIN AIN_PINS[] = {
 {"P9_39","AIN0",""}
,{"P9_40","AIN1",""}
,{"P9_41","AIN2",""}
,{"P9_42","AIN3",""}
,{"P9_43","AIN4",""}
,{"P9_44","AIN5",""}
,{"P9_45","AIN6",""}
};


const struct AINPIN* beaglebone_AIN_init_for_rawindex(int rawindex)
{
	//diect IOのやり方がわからないので、ファイルで代用.悔しい.
	char ocp_path[50];
	char helper_path[50];
	char AIN_filename[50];
	struct AINPIN* AINpin;

	//まず有効にする.
	if (!beaglebone_slot_install("cape-bone-iio"))
	{
		printf("can not install cape-bone-iio.\n");
		return NULL;
	}
	
	AINpin = &AIN_PINS[rawindex];
	if ( AINpin->filename[0] != '\0' )
	{//既に初期化済み
		return AINpin;
	}
	
	if (! beaglebone_findpath("/sys/devices", "ocp",ocp_path,sizeof(ocp_path)) )
	{
		printf("can not found /sys/devices/ocp* directory.\n");
		return NULL;
	}

	//デバイスファイルを探す.
	unsigned int retry = 0;
	AIN_filename[0] = '\0';
	for(retry = 0 ; retry < 1000 ; retry++ )
	{
		if ( beaglebone_findpath(ocp_path, "helper",helper_path,sizeof(helper_path)) )
		{
			snprintf(AIN_filename,sizeof(AIN_filename),"%s/%s",helper_path,AINpin->AINname);
			if ( isExist(AIN_filename) )
			{
				break;
			}
		}
		usleep(1000); //1msec sleep...
	}
	if (retry>=1000)
	{
		printf("can not found %s directory.\n",AIN_filename);
		return NULL;
	}
	strcpy(AINpin->filename,AIN_filename);
	return AINpin;
}

const struct AINPIN* beaglebone_AIN_init_for_name(const char* name)
{
	int i;
	for(i = 0 ; i < ARRAY_COUNTOF(AIN_PINS) ; i++ )
	{
		if (strcmp(AIN_PINS[i].portname,name) == 0 )
		{
			printf(" %s --> %d\n",name,i);
			return beaglebone_AIN_init_for_rawindex(i);
		}
		if (strcmp(AIN_PINS[i].AINname,name) == 0 )
		{
			printf(" %s --> %d\n",name,i);
			return beaglebone_AIN_init_for_rawindex(i);
		}
	}
	return NULL;
}

void beaglebone_AIN_clean(const struct AINPIN* AINpin)
{
}


float beaglebone_AIN_to_Volts(unsigned int value)
{
	return value * (1.8f / 4096 );
}


int beaglebone_AIN_read(const struct AINPIN* AINpin)
{
	int fd = open(AINpin->filename,O_RDONLY);
	if (fd<0)
	{
		printf("can not open %s  errno:%d\n",AINpin->filename,errno );
		return 0;
	}

	char buf[10];
	read(fd,buf,sizeof(buf));
	close(fd);

	return atoi(buf);
}




struct PWM{
	int fd_period;
	int fd_duty;
	int fd_run;
	char* slotname;
};
unsigned int g_pwm_init_count=0;

struct PWM* beaglebone_pwm_init(const char* portname)
{
	if (!beaglebone_slot_install("am33xx_pwm"))
	{
		printf("can not install am33xx_pwm.\n");
		return NULL;
	}

	char pwmname[50];
	snprintf(pwmname,sizeof(pwmname),"bone_pwm_%s",portname);
	if (!beaglebone_slot_install(pwmname))
	{
		printf("can not install %s.\n",pwmname);
		return NULL;
	}

	char ocp[50];
	if (! beaglebone_findpath("/sys/devices", "ocp",ocp,sizeof(ocp)) )
	{
		printf("can not found /sys/devices/bone_capemgr* directory.\n");
		return NULL;
	}

	char pwm_dir[50];
	char pwm_filename[50];
	snprintf(pwmname,sizeof(pwmname),"pwm_test_%s",portname);
	unsigned int retry = 0;
	for(retry = 0 ; retry < 1000 ; retry++ )
	{
		if ( beaglebone_findpath(ocp,pwmname,pwm_dir,sizeof(pwm_dir)) )
		{
			snprintf(pwm_filename,sizeof(pwm_filename),"%s/run",pwm_dir);
			if ( isExist(pwm_filename) )
			{
				break;
			}
		}
		usleep(1000); //1msec sleep...
	}
	if (retry>=1000)
	{
		printf("can not found %s/%s directory.\n",ocp,pwmname);
		return NULL;
	}

	struct PWM* pwmst = (struct PWM*)malloc(sizeof(struct PWM));
	pwmst->slotname = strdup(pwmname);
	
	snprintf(pwm_filename,sizeof(pwm_filename),"%s/run",pwm_dir);
	pwmst->fd_run = open(pwm_filename,O_RDWR);
	if (pwmst->fd_run<0)
	{
		printf("can not open %s  errno:%d\n",pwm_filename,errno );
		close(pwmst->fd_period);
		close(pwmst->fd_duty);
		free(pwmst);
		return NULL;
	}
	write(pwmst->fd_run,"0",1);

	
	snprintf(pwm_filename,sizeof(pwm_filename),"%s/period",pwm_dir);
	pwmst->fd_period = open(pwm_filename,O_RDWR);
	if (pwmst->fd_period<0)
	{
		printf("can not open %s  errno:%d\n",pwm_filename,errno );
		free(pwmst);
		return NULL;
	}

	snprintf(pwm_filename,sizeof(pwm_filename),"%s/duty",pwm_dir);
	pwmst->fd_duty = open(pwm_filename,O_RDWR);
	if (pwmst->fd_duty<0)
	{
		printf("can not open %s  errno:%d\n",pwm_filename,errno );
		close(pwmst->fd_period);
		free(pwmst);
		return NULL;
	}

	g_pwm_init_count++;
	return pwmst;
}

void beaglebone_pwm_clean(struct PWM* pwmst)
{
	close(pwmst->fd_period);
	close(pwmst->fd_duty);
	close(pwmst->fd_run);
//	beaglebone_slot_uninstall(pwmst->slotname); //消さない方がいいのもね
	free(pwmst->slotname);
	free(pwmst);
	
	g_pwm_init_count--;
	if (g_pwm_init_count <= 0)
	{
//		beaglebone_slot_uninstall("am33xx_pwm");
	}
}


inline void beaglebone_pwm_setall(struct PWM* pwmst,unsigned int period,unsigned int duty,int on)
{
	char buf[20];
	int len;
	len = snprintf(buf,sizeof(buf),"%u",duty);
	if ( write(pwmst->fd_duty,buf,len) < 0 )
	{
		printf("can not write duty %u  errno:%d",duty,errno);
		return ;
	}

	len = snprintf(buf,sizeof(buf),"%u",period);
	if ( write(pwmst->fd_period,buf,len) < 0 )
	{
		printf("can not write period %u  errno:%d",period,errno);
		return ;
	}

	if (on)
	{
		write(pwmst->fd_run,"1",1);
	}
	else
	{
		write(pwmst->fd_run,"0",1);
	}
}
inline void beaglebone_pwm_duty(struct PWM* pwmst,float persent)
{
	if (persent <= 0) persent = 0;
	if (persent >= 100) persent = 100;
	float duty = 500000 * (persent / 100);

	beaglebone_pwm_setall(pwmst,500000,(unsigned int)duty,1);
}

inline void beaglebone_pwm_on(struct PWM* pwmst)
{
	write(pwmst->fd_run,"1",1);
}
inline void beaglebone_pwm_off(struct PWM* pwmst)
{
	write(pwmst->fd_run,"0",1);
}




void usage()
{
	puts("");
	puts("bbtest Bealgebone black test");
	puts("-------------------------------------------------------------------------------");
	puts(" bbtest gpio_out P8_12 1          (write GPIO P8_12 port by 1)");
	puts(" bbtest gpio_out P8_12 0          (write GPIO P8_12 port by 0)");
	puts("");
	puts(" bbtest gpio_in P8_12             (read GPIO P8_12 port)");
	puts("");
	puts(" bbtest ain AIN0                  (read AIN0(P9_39) )");
	puts(" bbtest ain P9_39                 (read AIN0(P9_39) )");
	puts("");
	puts(" bbtest pwm P8_13 10000 5000 1    (period:10000 duty:5000 onoff:1)");
	puts(" bbtest pwm P8_13 10000 2000 0    (period:10000 duty:2000 onoff:0)");
	puts("");
	puts(" bbtest timer");
	puts("");
}


int mainbbtest(int argc, const char * argv[])
{
	if (strcmp(argv[1],"gpio_out") == 0)
	{//おまけ. gpio のテスト
		if (argc <= 3)
		{
			printf("GPIO PIN.    bbtest gpio_out P8_12 1   or   bbtest gpio_out P8_12 0 \n");
			return -1;
		}
		
		
		const struct GPIOPIN* gpio = beaglebone_gpio_init_for_name(argv[2],BEAGLEBONE_GPIO_OUT);
		if (!gpio)
		{
			printf("can not open GPIO PORT:%s\n",argv[2]);
			return -2;
		}

		if ( atoi(argv[3]) )
		{
			beaglebone_gpio_write_on(gpio);
		}
		else
		{
			beaglebone_gpio_write_off(gpio);
		}

		beaglebone_gpio_clean(gpio);
		return 1;
	}
	else if (strcmp(argv[1],"gpio_in") == 0)
	{//おまけ. gpio INのテスト
		if (argc <= 2)
		{
			printf("GPIO PIN.    bbtest gpio_in P8_12 \n");
			return -1;
		}
		
		
		const struct GPIOPIN* gpio = beaglebone_gpio_init_for_name(argv[2],BEAGLEBONE_GPIO_IN);
		if (!gpio)
		{
			printf("can not open GPIO PORT:%s\n",argv[2]);
			return -2;
		}

		int r = (int) beaglebone_gpio_read(gpio);
		printf("gpio read r:%d\n",r);

		beaglebone_gpio_clean(gpio);
		return 1;
	}
	else if (strcmp(argv[1],"ain") == 0)
	{//おまけ. AINのテスト
		if (argc <= 2)
		{
			printf("AIN PIN.    bbtest ain AIN0   or bbtest ain P9_39 \n");
			return -1;
		}
		
		
		const struct AINPIN* ain = beaglebone_AIN_init_for_name(argv[2]);
		if (!ain)
		{
			printf("can not open AIN PORT:%s\n",argv[2]);
			return -2;
		}

		int r = beaglebone_AIN_read(ain);
		printf("AIN read r:%d\n",r);

		beaglebone_AIN_clean(ain);
		return 1;
	}
	else if (strcmp(argv[1],"pwm") == 0)
	{//おまけ. PWMのテスト
		if (argc <= 5)
		{
			printf("pwm PIN period duty onoff.  bbtest pwm P8_13 10000 5000 1  (period:10000 duty:5000 onoff:1) \n");
			return -1;
		}

		struct PWM* pwm = beaglebone_pwm_init(argv[2]);
		if (!pwm)
		{
			printf("can not open PWM PORT:%s\n",argv[2]);
			return -2;
		}

		beaglebone_pwm_setall(pwm,atoi(argv[3]) ,atoi(argv[4]),atoi(argv[5]) );

		beaglebone_pwm_clean(pwm);
		return 1;
	}
	else if (strcmp(argv[1],"timer") == 0)
	{//おまけ.タイマーのテスト.
		puts("TIMER TEST. plases wait.");
		
		volatile unsigned int sec1 = beaglebone_dmtimer_get();
		sleep(1);
		volatile unsigned int sec2 = beaglebone_dmtimer_get();

		volatile unsigned int msec1 = beaglebone_dmtimer_get();
		usleep(1000);
		volatile unsigned int msec2 = beaglebone_dmtimer_get();

		volatile unsigned int usec1 = beaglebone_dmtimer_get();
		usleep(1);
		volatile unsigned int usec2 = beaglebone_dmtimer_get();

		printf("before:%u --> [sleep(1)]     --> after:%u    after - before = %u\n",sec1,sec2,sec2-sec1);
		printf("before:%u --> [usleep(1000)] --> after:%u    after - before = %u\n",msec1,msec2,msec2-msec1);
		printf("before:%u --> [usleep(1)]    --> after:%u    after - before = %u\n",usec1,usec2,usec2-usec1);

		return 1;
	}
	return -1;
}


int main(int argc, const char * argv[])
{
	if (argc <= 1)
	{
		usage();
		return -1;
	}

	int r;
	r = beaglebone_init();
	if (r <= 0)
	{
		printf("beaglebone_init ERROR! r:%d\n",r);
		usage();
		return -1;
	}

	r = mainbbtest(argc,argv);
	if (r <= 0)
	{
		printf("mainbbtest ERROR! r:%d\n",r);
		usage();
		beaglebone_clean();
		return -1;
	}

	beaglebone_clean();
}

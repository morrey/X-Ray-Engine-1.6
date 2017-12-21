#ifndef _INC_CPUID
#define _INC_CPUID

#define _CPU_FEATURE_MMX 0x0001
#define _CPU_FEATURE_SSE 0x0002
#define _CPU_FEATURE_SSE2 0x0004
#define _CPU_FEATURE_3DNOW 0x0008

#define _CPU_FEATURE_SSE3 0x0010
#define _CPU_FEATURE_SSSE3 0x0020
#define _CPU_FEATURE_SSE4_1 0x0040
#define _CPU_FEATURE_SSE4_2 0x0080

#define _CPU_FEATURE_MWAIT 0x0100
#define _CPU_FEATURE_HTT 0x0200

enum class CPUFeature : unsigned
{
	MMX = 1 << 0,
	MMXExt = 1 << 1,
	MWait = 1 << 2,
	HT = 1 << 3,

	SSE = 1 << 4,
	SSE2 = 1 << 5,
	SSE3 = 1 << 6,
	SSSE3 = 1 << 7,
	SSE41 = 1 << 8,
	SSE4a = 1 << 9,
	SSE42 = 1 << 10,

	AVX = 1 << 11,
	AVX2 = 1 << 12,
	AVX512F = 1 << 13,
	AVX512PF = 1 << 14,
	AVX512ER = 1 << 15,
	AVX512CD = 1 << 16,

	AMD_3DNow = 1 << 17,
	AMD_3DNowExt = 1 << 18
};

struct _processor_info
{
    char v_name[13]; // vendor name
    char model_name[49]; // Name of model eg. Intel_Pentium_Pro

    unsigned char family; // family of the processor, eg. Intel_Pentium_Pro is family 6 processor
    unsigned char model; // model of processor, eg. Intel_Pentium_Pro is model 1 of family 6 processor
    unsigned char stepping; // Processor revision number

    unsigned int feature; // processor Feature ( same as return value).

    unsigned int n_cores; // number of available physical cores
    unsigned int n_threads; // number of available logical threads

    unsigned int affinity_mask; // recommended affinity mask
    // all processors available to process
    // except 2nd (and upper) logical threads
    // of the same physical core

	bool isAmd;				// AMD flag
	bool isIntel;			// IntelCore flag

	bool hasFeature(const CPUFeature _feature) const noexcept
	{
		return (feature & static_cast<unsigned>(_feature));
	}
};

int _cpuid(_processor_info*);

#endif

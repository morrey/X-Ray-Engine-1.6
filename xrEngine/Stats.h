// Stats.h: interface for the CStats class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATS_H__4C8D1860_0EE2_11D4_B4E3_4854E82A090D__INCLUDED_)
#define AFX_STATS_H__4C8D1860_0EE2_11D4_B4E3_4854E82A090D__INCLUDED_
#pragma once

class ENGINE_API CGameFont;

DECLARE_MESSAGE(Stats);

class ENGINE_API CStats : public pureRender
{
private:
    CGameFont* statsFont;
    float fMem_calls;
    xr_vector<shared_str> errors;

public:
    CStats();
    ~CStats();

    void Show(void);
    virtual void OnRender();
    void OnDeviceCreate(void);
    void OnDeviceDestroy(void);

private:
    void FilteredLog(const char* s);
};

enum
{
    st_sound = (1 << 0),
    st_sound_min_dist = (1 << 1),
    st_sound_max_dist = (1 << 2),
    st_sound_ai_dist = (1 << 3),
    st_sound_info_name = (1 << 4),
    st_sound_info_object = (1 << 5),
};

extern Flags32 g_stats_flags;

#endif // !defined(AFX_STATS_H__4C8D1860_0EE2_11D4_B4E3_4854E82A090D__INCLUDED_)

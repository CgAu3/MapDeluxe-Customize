void LoadGraAssocTable(u32 gra_map);

struct GRA_ASSOC_LIST
{
	CList<u16> left,right,up,down;
};
extern GRA_ASSOC_LIST* GraAssocLa;
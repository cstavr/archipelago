#ifndef __XOBJ_H__
#define __XOBJ_H__

#include <sys/util.h>
#include <xtypes/xlock.h>
#include <xtypes/xheap.h>
#include <xtypes/domain.h>

#define X_ALLOC ((uint32_t) (1 << 0))

struct xobject_header {
	XPTR_TYPE(struct xseg_object_handler) obj_h;
};

struct xobject {
	uint32_t magic;
	uint64_t size;
	xptr next;
};

struct xobject_h {
	uint32_t magic;
	uint64_t obj_size;
	uint32_t flags;
	XPTR_TYPE(void) container;
	xptr heap;
	xptr allocated;
	xptr list;
	struct xlock lock;
};

void *xobj_get_obj(struct xobject_h * obj_h, uint32_t flags);
void xobj_put_obj(struct xobject_h * obj_h, void *ptr);
int xobj_alloc_obj(struct xobject_h * obj_h, uint64_t nr);
int xobj_handler_init(struct xobject_h *obj_h, void *container,
		uint32_t magic,	uint64_t size, struct xheap *heap);

//TODO 
//xobj_handler_destroy()
//releases allocated pages
//
//maybe we need lock free versions of get/put obj
//
//also an
//unsigned long xobj_get_objs(obj_h, flags, uint64_t nr, void **buf)
//which will put nr objects in buf
#endif
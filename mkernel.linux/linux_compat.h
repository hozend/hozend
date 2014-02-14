#include <linux/version.h>


#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
#error "Jeeez! And I thought my granny looked ancient... upgrade your kernel. now!"
#elsif LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
#define LINUX30
#endif

#ifndef LINUX20
#define FINODE(f)	((f)->f_dentry->d_inode)
#else
#define FINODE(f)	((f)->f_inode)
#endif

#ifdef LINUX20
inline int copy_from_user(void *dst, const void *src, unsigned long len)
{
  int err;

  if(err = verify_area(VERIFY_READ, src, len))
    return err;

  memcpy_fromfs(dst, src, len);
  return 0;
}

inline int copy_to_user(void *dst, const void *src, int len)
{
  int err;

  if(err = verify_area(VERIFY_WRITE, dst, len))
    return err;

  memcpy_tofs(dst, src, len);
  return 0;
}
#endif

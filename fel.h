#ifndef __FEL_H__
#define __FEL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <x.h>

struct xfel_ctx_t;
struct chip_t;

struct xfel_ctx_t {
	libusb_device_handle * hdl;
	int epout;
	int epin;
	struct {
		char signature[8];
		uint32_t id;
		uint32_t unknown_0a;
		uint16_t protocol;
		uint8_t  unknown_12;
		uint8_t  unknown_13;
		uint32_t scratchpad;
		uint32_t pad[2];
	} version;
	struct chip_t * chip;
};

struct chip_t {
	char * name;
	uint32_t id;

	int (*reset)(struct xfel_ctx_t * ctx);
	int (*sid)(struct xfel_ctx_t * ctx);
	int (*jtag)(struct xfel_ctx_t * ctx);
	int (*ddr)(struct xfel_ctx_t * ctx);
};

#define R32(reg)		fel_read32(ctx, reg)
#define W32(reg, val)	fel_write(ctx, addr, val)

int fel_init(struct xfel_ctx_t * ctx);
void fel_exec(struct xfel_ctx_t * ctx, uint32_t addr);
uint32_t fel_read32(struct xfel_ctx_t * ctx, uint32_t addr);
void fel_write32(struct xfel_ctx_t * ctx, uint32_t addr, uint32_t val);
void fel_read(struct xfel_ctx_t * ctx, uint32_t addr, void * buf, size_t len, int progress);
void fel_write(struct xfel_ctx_t * ctx, uint32_t addr, void * buf, size_t len, int progress);

int fel_chip_reset(struct xfel_ctx_t * ctx);
int fel_chip_sid(struct xfel_ctx_t * ctx);
int fel_chip_jtag(struct xfel_ctx_t * ctx);
int fel_chip_ddr(struct xfel_ctx_t * ctx);

#ifdef __cplusplus
}
#endif

#endif /* __FEL_H__ */
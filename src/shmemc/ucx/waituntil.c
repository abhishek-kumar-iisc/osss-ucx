/* For license: see LICENSE file at top-level */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#include "shmemu.h"
#include "shmemc.h"

#include "yielder.h"

#include <ucp/api/ucp.h>

#if 0
#define VOLATILIZE(_type, _var) (* ( volatile _type *) (_var))
#endif

#define COMMS_CTX_WAIT_SIZE(_size, _opname)                             \
    void                                                                \
    shmemc_ctx_wait_until_##_opname##_size(shmem_ctx_t ctx,             \
                                           int##_size##_t *var,         \
                                           int##_size##_t value)        \
    {                                                                   \
        shmemc_context_h ch = (shmemc_context_h) ctx;                   \
                                                                        \
        do {                                                            \
            shmemc_progress();                                          \
            yielder();                                                  \
            ucp_worker_wait_mem(ch->w, var);                            \
        } while (shmemc_ctx_test_##_opname##_size(ctx, var, value) == 0); \
    }

COMMS_CTX_WAIT_SIZE(16, eq)
COMMS_CTX_WAIT_SIZE(32, eq)
COMMS_CTX_WAIT_SIZE(64, eq)

COMMS_CTX_WAIT_SIZE(16, ne)
COMMS_CTX_WAIT_SIZE(32, ne)
COMMS_CTX_WAIT_SIZE(64, ne)

COMMS_CTX_WAIT_SIZE(16, gt)
COMMS_CTX_WAIT_SIZE(32, gt)
COMMS_CTX_WAIT_SIZE(64, gt)

COMMS_CTX_WAIT_SIZE(16, le)
COMMS_CTX_WAIT_SIZE(32, le)
COMMS_CTX_WAIT_SIZE(64, le)

COMMS_CTX_WAIT_SIZE(16, lt)
COMMS_CTX_WAIT_SIZE(32, lt)
COMMS_CTX_WAIT_SIZE(64, lt)

COMMS_CTX_WAIT_SIZE(16, ge)
COMMS_CTX_WAIT_SIZE(32, ge)
COMMS_CTX_WAIT_SIZE(64, ge)

/* This file is generated by venus-protocol.  See vn_protocol_driver.h. */

/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#ifndef VN_PROTOCOL_DRIVER_PIPELINE_LAYOUT_H
#define VN_PROTOCOL_DRIVER_PIPELINE_LAYOUT_H

#include "vn_ring.h"
#include "vn_protocol_driver_structs.h"

static inline size_t vn_sizeof_vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreatePipelineLayout_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_simple_pointer(pCreateInfo);
    if (pCreateInfo)
        cmd_size += vn_sizeof_VkPipelineLayoutCreateInfo(pCreateInfo);
    cmd_size += vn_sizeof_simple_pointer(pAllocator);
    if (pAllocator)
        assert(false);
    cmd_size += vn_sizeof_simple_pointer(pPipelineLayout);
    if (pPipelineLayout)
        cmd_size += vn_sizeof_VkPipelineLayout(pPipelineLayout);

    return cmd_size;
}

static inline void vn_encode_vkCreatePipelineLayout(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreatePipelineLayout_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    if (vn_encode_simple_pointer(enc, pCreateInfo))
        vn_encode_VkPipelineLayoutCreateInfo(enc, pCreateInfo);
    if (vn_encode_simple_pointer(enc, pAllocator))
        assert(false);
    if (vn_encode_simple_pointer(enc, pPipelineLayout))
        vn_encode_VkPipelineLayout(enc, pPipelineLayout);
}

static inline size_t vn_sizeof_vkCreatePipelineLayout_reply(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkCreatePipelineLayout_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    VkResult ret;
    cmd_size += vn_sizeof_VkResult(&ret);
    /* skip device */
    /* skip pCreateInfo */
    /* skip pAllocator */
    cmd_size += vn_sizeof_simple_pointer(pPipelineLayout);
    if (pPipelineLayout)
        cmd_size += vn_sizeof_VkPipelineLayout(pPipelineLayout);

    return cmd_size;
}

static inline VkResult vn_decode_vkCreatePipelineLayout_reply(struct vn_cs_decoder *dec, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkCreatePipelineLayout_EXT);

    VkResult ret;
    vn_decode_VkResult(dec, &ret);
    /* skip device */
    /* skip pCreateInfo */
    /* skip pAllocator */
    if (vn_decode_simple_pointer(dec)) {
        vn_decode_VkPipelineLayout(dec, pPipelineLayout);
    } else {
        pPipelineLayout = NULL;
    }

    return ret;
}

static inline size_t vn_sizeof_vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroyPipelineLayout_EXT;
    const VkFlags cmd_flags = 0;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type) + vn_sizeof_VkFlags(&cmd_flags);

    cmd_size += vn_sizeof_VkDevice(&device);
    cmd_size += vn_sizeof_VkPipelineLayout(&pipelineLayout);
    cmd_size += vn_sizeof_simple_pointer(pAllocator);
    if (pAllocator)
        assert(false);

    return cmd_size;
}

static inline void vn_encode_vkDestroyPipelineLayout(struct vn_cs_encoder *enc, VkCommandFlagsEXT cmd_flags, VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroyPipelineLayout_EXT;

    vn_encode_VkCommandTypeEXT(enc, &cmd_type);
    vn_encode_VkFlags(enc, &cmd_flags);

    vn_encode_VkDevice(enc, &device);
    vn_encode_VkPipelineLayout(enc, &pipelineLayout);
    if (vn_encode_simple_pointer(enc, pAllocator))
        assert(false);
}

static inline size_t vn_sizeof_vkDestroyPipelineLayout_reply(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
    const VkCommandTypeEXT cmd_type = VK_COMMAND_TYPE_vkDestroyPipelineLayout_EXT;
    size_t cmd_size = vn_sizeof_VkCommandTypeEXT(&cmd_type);

    /* skip device */
    /* skip pipelineLayout */
    /* skip pAllocator */

    return cmd_size;
}

static inline void vn_decode_vkDestroyPipelineLayout_reply(struct vn_cs_decoder *dec, VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
    VkCommandTypeEXT command_type;
    vn_decode_VkCommandTypeEXT(dec, &command_type);
    assert(command_type == VK_COMMAND_TYPE_vkDestroyPipelineLayout_EXT);

    /* skip device */
    /* skip pipelineLayout */
    /* skip pAllocator */
}

static inline void vn_submit_vkCreatePipelineLayout(struct vn_ring *vn_ring, VkCommandFlagsEXT cmd_flags, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout, struct vn_ring_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkCreatePipelineLayout_reply(device, pCreateInfo, pAllocator, pPipelineLayout) : 0;

    struct vn_cs_encoder *enc = vn_ring_submit_command_init(vn_ring, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkCreatePipelineLayout(enc, cmd_flags, device, pCreateInfo, pAllocator, pPipelineLayout);
        vn_ring_submit_command(vn_ring, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline void vn_submit_vkDestroyPipelineLayout(struct vn_ring *vn_ring, VkCommandFlagsEXT cmd_flags, VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator, struct vn_ring_submit_command *submit)
{
    uint8_t local_cmd_data[VN_SUBMIT_LOCAL_CMD_SIZE];
    void *cmd_data = local_cmd_data;
    size_t cmd_size = vn_sizeof_vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
    if (cmd_size > sizeof(local_cmd_data)) {
        cmd_data = malloc(cmd_size);
        if (!cmd_data)
            cmd_size = 0;
    }
    const size_t reply_size = cmd_flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT ? vn_sizeof_vkDestroyPipelineLayout_reply(device, pipelineLayout, pAllocator) : 0;

    struct vn_cs_encoder *enc = vn_ring_submit_command_init(vn_ring, submit, cmd_data, cmd_size, reply_size);
    if (cmd_size) {
        vn_encode_vkDestroyPipelineLayout(enc, cmd_flags, device, pipelineLayout, pAllocator);
        vn_ring_submit_command(vn_ring, submit);
        if (cmd_data != local_cmd_data)
            free(cmd_data);
    }
}

static inline VkResult vn_call_vkCreatePipelineLayout(struct vn_ring *vn_ring, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
    VN_TRACE_FUNC();

    struct vn_ring_submit_command submit;
    vn_submit_vkCreatePipelineLayout(vn_ring, VK_COMMAND_GENERATE_REPLY_BIT_EXT, device, pCreateInfo, pAllocator, pPipelineLayout, &submit);
    struct vn_cs_decoder *dec = vn_ring_get_command_reply(vn_ring, &submit);
    if (dec) {
        const VkResult ret = vn_decode_vkCreatePipelineLayout_reply(dec, device, pCreateInfo, pAllocator, pPipelineLayout);
        vn_ring_free_command_reply(vn_ring, &submit);
        return ret;
    } else {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
}

static inline void vn_async_vkCreatePipelineLayout(struct vn_ring *vn_ring, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
    struct vn_ring_submit_command submit;
    vn_submit_vkCreatePipelineLayout(vn_ring, 0, device, pCreateInfo, pAllocator, pPipelineLayout, &submit);
}

static inline void vn_async_vkDestroyPipelineLayout(struct vn_ring *vn_ring, VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
    struct vn_ring_submit_command submit;
    vn_submit_vkDestroyPipelineLayout(vn_ring, 0, device, pipelineLayout, pAllocator, &submit);
}

#endif /* VN_PROTOCOL_DRIVER_PIPELINE_LAYOUT_H */

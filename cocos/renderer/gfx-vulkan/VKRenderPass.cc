#include "VKStd.h"

#include "VKCommands.h"
#include "VKRenderPass.h"

namespace cc {
namespace gfx {

CCVKRenderPass::CCVKRenderPass(GFXDevice *device)
: GFXRenderPass(device) {
}

CCVKRenderPass::~CCVKRenderPass() {
}

bool CCVKRenderPass::initialize(const GFXRenderPassInfo &info) {
    _colorAttachments = info.colorAttachments;
    _depthStencilAttachment = info.depthStencilAttachment;
    _subPasses = info.subPasses;

    _gpuRenderPass = CC_NEW(CCVKGPURenderPass);
    _gpuRenderPass->colorAttachments = _colorAttachments;
    _gpuRenderPass->depthStencilAttachment = _depthStencilAttachment;
    _gpuRenderPass->subPasses = _subPasses;
    CCVKCmdFuncCreateRenderPass((CCVKDevice *)_device, _gpuRenderPass);

    _hash = computeHash();
    _status = GFXStatus::SUCCESS;

    return true;
}

void CCVKRenderPass::destroy() {
    if (_gpuRenderPass) {
        CCVKCmdFuncDestroyRenderPass((CCVKDevice *)_device, _gpuRenderPass);
        CC_DELETE(_gpuRenderPass);
        _gpuRenderPass = nullptr;
    }

    _status = GFXStatus::UNREADY;
}

} // namespace gfx
} // namespace cc
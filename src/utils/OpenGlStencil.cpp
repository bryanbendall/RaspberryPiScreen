#include "OpenGlStencil.h"

#include <external/glfw/include/GLFW/glfw3.h>
#include <rlgl.h>

// Stencil masks
void beginStencil()
{
    rlDrawRenderBatchActive();
    glEnable(GL_STENCIL_TEST);
}

void beginStencilMask()
{
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5f);
}

void endStencilMask()
{
    rlDrawRenderBatchActive();
    glDisable(GL_ALPHA_TEST);
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void endStencil()
{
    rlDrawRenderBatchActive();
    glDisable(GL_STENCIL_TEST);
}
#include "uClassFactory.h"
#include "uDebugPrinter.h"
uClassFactory::uClassFactory()
{

}

uClassFactory &uClassFactory::getInstance()
{
    static uClassFactory instance;
    return instance;
}

uInheritable * uClassFactory::createClass(uClassType type, std::string const& name)
{
    switch (type) {

        case eBaseClass:
            return new uBaseClass(name);
            uDebugPrinter::printText("shit");
            break;
        case eInterface:
            return new uInterface(name);
            uDebugPrinter::printText("shit");

            break;
        case eChildClass:
            return new uChildClass(name);
            uDebugPrinter::printText("shit");

            break;
        default:
            return NULL;
            uDebugPrinter::printText("shit");
            break;
    }
}

uInheritable * uClassFactory::createClass(uClassType type, uAccess access, const std::string &name, TParameters &attributes, TMethods &methods, TReferences &references, uInheritable *base)
{
    switch (type) {

        case eBaseClass:
            return new uBaseClass(access, name, attributes, methods, references);
            uDebugPrinter::printText("base factory");
            break;
        case eInterface:
            return new uInterface(access, name, attributes, methods, references);
             uDebugPrinter::printText("interface factory");
            break;
        case eChildClass:
            return new uChildClass(access, name, attributes, methods, references, base);
             uDebugPrinter::printText("child factory");
            break;
        default:
            return NULL;
            uDebugPrinter::printText("shit factory");
            break;
    }

}


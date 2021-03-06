
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_print_MultiDocPrintService__
#define __javax_print_MultiDocPrintService__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

extern "Java"
{
  namespace javax
  {
    namespace print
    {
        class DocFlavor;
        class DocPrintJob;
        class MultiDocPrintJob;
        class MultiDocPrintService;
        class ServiceUIFactory;
      namespace attribute
      {
          class Attribute;
          class AttributeSet;
          class PrintServiceAttribute;
          class PrintServiceAttributeSet;
      }
      namespace event
      {
          class PrintServiceAttributeListener;
      }
    }
  }
}

class javax::print::MultiDocPrintService : public ::java::lang::Object
{

public:
  virtual ::javax::print::MultiDocPrintJob * createMultiDocPrintJob() = 0;
  virtual ::javax::print::DocPrintJob * createPrintJob() = 0;
  virtual ::javax::print::attribute::PrintServiceAttribute * getAttribute(::java::lang::Class *) = 0;
  virtual ::javax::print::attribute::PrintServiceAttributeSet * getAttributes() = 0;
  virtual ::java::lang::Object * getDefaultAttributeValue(::java::lang::Class *) = 0;
  virtual ::java::lang::String * getName() = 0;
  virtual ::javax::print::ServiceUIFactory * getServiceUIFactory() = 0;
  virtual JArray< ::java::lang::Class * > * getSupportedAttributeCategories() = 0;
  virtual ::java::lang::Object * getSupportedAttributeValues(::java::lang::Class *, ::javax::print::DocFlavor *, ::javax::print::attribute::AttributeSet *) = 0;
  virtual JArray< ::javax::print::DocFlavor * > * getSupportedDocFlavors() = 0;
  virtual ::javax::print::attribute::AttributeSet * getUnsupportedAttributes(::javax::print::DocFlavor *, ::javax::print::attribute::AttributeSet *) = 0;
  virtual jboolean isAttributeCategorySupported(::java::lang::Class *) = 0;
  virtual jboolean isAttributeValueSupported(::javax::print::attribute::Attribute *, ::javax::print::DocFlavor *, ::javax::print::attribute::AttributeSet *) = 0;
  virtual jboolean isDocFlavorSupported(::javax::print::DocFlavor *) = 0;
  virtual void addPrintServiceAttributeListener(::javax::print::event::PrintServiceAttributeListener *) = 0;
  virtual void removePrintServiceAttributeListener(::javax::print::event::PrintServiceAttributeListener *) = 0;
  static ::java::lang::Class class$;
} __attribute__ ((java_interface));

#endif // __javax_print_MultiDocPrintService__

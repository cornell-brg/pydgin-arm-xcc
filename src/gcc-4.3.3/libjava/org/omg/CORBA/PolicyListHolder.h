
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __org_omg_CORBA_PolicyListHolder__
#define __org_omg_CORBA_PolicyListHolder__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

extern "Java"
{
  namespace org
  {
    namespace omg
    {
      namespace CORBA
      {
          class Policy;
          class PolicyListHolder;
          class TypeCode;
        namespace portable
        {
            class InputStream;
            class OutputStream;
        }
      }
    }
  }
}

class org::omg::CORBA::PolicyListHolder : public ::java::lang::Object
{

public:
  PolicyListHolder();
  PolicyListHolder(JArray< ::org::omg::CORBA::Policy * > *);
  void _read(::org::omg::CORBA::portable::InputStream *);
  void _write(::org::omg::CORBA::portable::OutputStream *);
  ::org::omg::CORBA::TypeCode * _type();
  JArray< ::org::omg::CORBA::Policy * > * __attribute__((aligned(__alignof__( ::java::lang::Object)))) value;
  static ::java::lang::Class class$;
};

#endif // __org_omg_CORBA_PolicyListHolder__

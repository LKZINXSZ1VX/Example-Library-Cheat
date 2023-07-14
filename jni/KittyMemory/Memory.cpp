
#include "Memory.h"


Memory::Memory() {
  _address = 0;
  _size    = 0;
  _orig_code.clear();
  _patch_code.clear();
}

Memory::Memory(const char *libraryName, uintptr_t address, const void *patch_code, size_t patch_size) {
  Memory();

  if (libraryName == NULL || address == 0 || patch_code == NULL || patch_size < 1)
    return;

  _address = Ptrace::getAbsoluteAddress(libraryName, address);
  if(_address == 0) return;
  
  _size    = patch_size;

  _orig_code.resize(patch_size);
  _patch_code.resize(patch_size);

  // initialize patch & backup current content
  Ptrace::memRead(&_patch_code[0], patch_code, patch_size);
  Ptrace::memRead(&_orig_code[0], reinterpret_cast<const void *>(_address), patch_size);
}

   Memory::~Memory() {
     // clean up
     _orig_code.clear();
     _patch_code.clear();
   }

  bool Memory::isValid() const {
    return (_address != 0 && _size > 0
            && _orig_code.size() == _size && _patch_code.size() == _size);
  }

  size_t Memory::get_PatchSize() const{
    return _size;
  }

  uintptr_t Memory::get_TargetAddress() const{
    return _address;
  }

  bool Memory::Restore() {
    if (!isValid()) return false;
    return Ptrace::memWrite(reinterpret_cast<void *>(_address), &_orig_code[0], _size) == Memory_Status::SUCCESS;
  }

  bool Memory::Modify() {
    if (!isValid()) return false;
    return (Ptrace::memWrite(reinterpret_cast<void *>(_address), &_patch_code[0], _size) == Memory_Status::SUCCESS);
  }

  std::string Memory::ToHexString() {
    if (!isValid()) return std::string("0xInvalid");
    return Ptrace::read2HexStr(reinterpret_cast<const void *>(_address), _size);
  }

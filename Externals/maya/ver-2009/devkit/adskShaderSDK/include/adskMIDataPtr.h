// ==========================================================================
// Copyright 2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================

/*!
  \file
  \brief A smart pointer class to manage database access calls.

  Smart pointer class that manages the accessing and unpinning of
  mental ray database elements.  This guarantees the coherence of
  database elment reference counts by unpinning when the pointer is
  destroyed (e.g.  when the local stack is unrolled) This makes
  database ref counts break/return-safe, and generally foolproof.
*/

#ifndef ADSK_MI_DATA_PTR_H
#define ADSK_MI_DATA_PTR_H

#if defined __cplusplus

#ifndef SHADER_H
#include <shader.h>
#endif

// Do not move this
#include "adskShaderSDKNamespaceBegin.h"

/*!

  \brief Smart pointer class that manages the accessing and unpinning
  of mental ray database elements.

  \tparam DataStruct The type of the data the smart pointer will reference.
*/
template<typename DataStruct>
class MIDataPtr{

  public:

    /*!
      \brief Default constructor
    */
    MIDataPtr()
    {
        mData = 0;
        mTag = 0;
        mBadEndian = false;
    }

    /*!
      \brief Construct by database tag

      \param[in] pTag The \c miTag to look up.
    */
    MIDataPtr(const miTag& pTag)
    {
        mData = pTag ? (DataStruct*)mi_db_access(pTag) : 0;
        mTag = mData ? pTag : 0;
        mBadEndian = false;
    }

    /*!
      \brief Construct using pre-accessed data

      \param[in] pData The pre-accessed data.
      \param[in] pTag The \c miTag associated with the data.
      \param[in] pBadEndian True if an endian switch is necessary.
    */
    MIDataPtr(DataStruct* pData, const miTag& pTag, bool pBadEndian = false)
    {
        if (pData) {
            mData = pData;
            mTag = pTag;
        } else {
            mData = 0;
            mTag = 0;
        }
        mBadEndian = pBadEndian;
    }

    /*!
      \brief Copy constructor

      \attention This smart pointer passes ownership, so the smart
      pointer being constructed from will no longer be valid.

      \param pPtr The MIDataPtr to construct from.
    */
    MIDataPtr(const MIDataPtr& pPtr)
    {
        copy(pPtr);
    }

    /*!
      \brief Destructor
    */
    ~MIDataPtr()
    {
        if (!isNull()) mi_db_unpin(mTag);
    }

    /*!
      \brief Reinitialization with new database tag

      \param pTag The \c miTag to use for reinitialization.
    */
    void set(const miTag& pTag)
    {
        unbind();
        mData = pTag ? (DataStruct*)mi_db_access(pTag) : 0;
        mTag = mData ? pTag : 0;
        mBadEndian = false;
    }

    /*!
      \brief Assignment operator

      \attention This smart pointer passes ownership, so the smart
      pointer being assigned from will no longer be valid.

      \param pPtr The MIDataPtr to assign from.
    */
    MIDataPtr<DataStruct>& operator = (const MIDataPtr& pPtr)
        {
            if (mTag != pPtr.mTag)
            {
                unbind();
                copy(pPtr);
            }
            return *this;
        }

    /*!
      \brief Dereferencing operator

      \return The underlying pointer.
    */
    DataStruct* operator->() 
    {
        return mData;
    }

    /*!
      \brief Array access operator

      \param pIndex The index in the DataStruct array. Bounds
      checking is the responsability of the user.

      \return The array element.
    */
    DataStruct &operator[](int pIndex){
        return mData[pIndex];
    }

    /*!
      \brief Const array access operator

      \param pIndex The index in the DataStruct array. Bounds
      checking is the responsability of the user.

      \return The (const) array element.
    */
    const DataStruct &operator[](int pIndex) const {
        return mData[pIndex];
    }

    /*!
      \brief Pointer access

      \return The underlying pointer.
    */
    DataStruct *get() const {
        return mData;
    }

    /*!
      \brief Const dereferencing operator

      \return The underlying (const) pointer.
    */
    const DataStruct* operator->() const
    {
        return mData;
    }

    /*!
      \brief Check pointer nullness

      \return True if the pointer is null.
    */
    bool isNull() const
    {
        return (mTag == 0 || mData == 0);
    }

    /*!
      \brief Get the endianness of the data.

      \return True if the data has an endianness which needs to be switched.
    */
    bool badEndian() const
    {
        return mBadEndian;
    }

    /*!
      \brief Implicit cast to bool

      \return True if the pointer is non-null, false otherwise.
    */
    operator bool () const
    {
        return (!isNull());
    }

    /*!
      \brief Unreference pointed data
    */
    void unbind()
    {
        if (!isNull())
        {
            mi_db_unpin(mTag);
            mTag = 0;
            mData = 0;
            mBadEndian = false;
        }
    }

  private:

    /*!
      \brief Take ownership of another smart pointer.

      \attention This function takes ownership, so the smart
      pointer to copy will no longer be valid.

      \param pPtr The smart pointer to copy.
    */
    void copy(const MIDataPtr& pPtr)
    {
        if (!pPtr.isNull())
        {
            mTag = pPtr.mTag;
            mBadEndian = pPtr.mBadEndian;

            // we use the pointer from the source rather that the one
            // returned by mi_db_access in case we are using an offset.
            mData = pPtr.mData; 

            // We steal ownership by nullifying the source of the copy.
            // This way, there is no need to increment the database
            // ref count with an additional call to mi_db_access, and the 
            // source's destructor will be a no-op.
            pPtr.mTag = 0;
            pPtr.mData = 0;
        }
        else
        {
            mTag = 0;
            mData = 0;
            mBadEndian = false;
        }
    }

    mutable DataStruct* mData; //!< The binary data block.
    mutable miTag       mTag; //!< The \c miTag for the binary data block.
    bool                mBadEndian; //!< True if the binary data block needs to have an endian switch.
};

// Do not move this
#include "adskShaderSDKNamespaceEnd.h"

#endif // __cplusplus
#endif // ADSK_MI_DATA_PTR_H

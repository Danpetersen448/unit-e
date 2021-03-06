// Copyright (c) 2018-2019 The Unit-e developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UNITE_STAKING_COIN_H
#define UNITE_STAKING_COIN_H

#include <amount.h>
#include <blockchain/blockchain_types.h>
#include <chain.h>
#include <primitives/transaction.h>
#include <script/script.h>
#include <uint256.h>

class CBlockIndex;

namespace staking {

//! \brief A coin that is potentially stakeable.
//!
//! A coin is basically a reference to a CTxOut of a transaction in a block.
class Coin {

 public:
  Coin(const CBlockIndex *containing_block, const COutPoint &out_point, const CTxOut &tx_out)
      : m_containing_block(containing_block), m_out_point(out_point), m_tx_out(tx_out) {}

  //! \brief The hash of the block containing the staked coin.
  const uint256 &GetBlockHash() const { return *m_containing_block->phashBlock; }

  //! \brief The time of the block containing the staked coin.
  blockchain::Time GetBlockTime() const { return m_containing_block->nTime; };

  //! \brief The amount of stake.
  CAmount GetAmount() const { return m_tx_out.nValue; };

  //! \brief The height at which this coin is included in a block.
  blockchain::Height GetHeight() const { return static_cast<blockchain::Height>(m_containing_block->nHeight); }

  //! \brief The id of the transaction which spends this piece of stake.
  //!
  //! This is the same as `GetOutPoint().hash`.
  const uint256 &GetTransactionId() const { return m_out_point.hash; }

  //! \brief The index of the spending output.
  //!
  //! This is the same as `GetOutPoint().n`
  std::uint32_t GetOutputIndex() const { return m_out_point.n; }

  //! \brief The outpoint of the staking output (txid and out index).
  const COutPoint &GetOutPoint() const { return m_out_point; }

  //! \brief The locking script of the coin.
  const CScript &GetScriptPubKey() const { return m_tx_out.scriptPubKey; }

  bool operator==(const Coin &other) const {
    return GetOutPoint() == other.GetOutPoint();
  }

  bool operator!=(const Coin &other) const {
    return !(*this == other);
  }

  std::string ToString() const;

 private:
  //! The index entry of the block that contains this coin.
  const CBlockIndex *const m_containing_block;

  //! The outpoint which spends this stake.
  const COutPoint m_out_point;

  //! The actual CTxOut that spends this stake - featuring amount and locking script.
  const CTxOut m_tx_out;
};

//! \brief A comparator that compares coins by amount.
//!
//! Compares coins by their properties in the following order:
//! - Amount, descending (bigger coins first)
//! - Height, ascending (older coins first)
//! - TransactionHash, ascending
//! - OutputIndex, ascending
//!
//! This is not an intrinsic compare function on Coin as this
//! is in no way how coins would be sorted in the general case.
//! While the properties Amount and Height should always be the
//! same for two coins for which the OutPoint is the same, a user
//! of this class might not follow this rule (for example in tests)
//! in which case `==` and `!=` might differ from `<`. In other words:
//! A proper `<` on Coin would take into account only the properties
//! which `==` and `!=` take into account, but this comparator takes
//! into account more properties.
struct CoinByAmountComparator {
  bool operator()(const Coin &left, const Coin &right) const {
    if (left.GetAmount() > right.GetAmount()) {
      return true;
    }
    if (left.GetAmount() < right.GetAmount()) {
      return false;
    }
    if (left.GetHeight() < right.GetHeight()) {
      return true;
    }
    if (left.GetHeight() > right.GetHeight()) {
      return false;
    }
    if (left.GetTransactionId() < right.GetTransactionId()) {
      return true;
    }
    if (left.GetTransactionId() != right.GetTransactionId()) {
      return false;
    }
    return left.GetOutputIndex() < right.GetOutputIndex();
  }
};

using CoinSet = std::set<Coin, CoinByAmountComparator>;

}  // namespace staking

#endif  // UNITE_STAKING_COIN_H

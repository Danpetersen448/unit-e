// Copyright (c) 2018-2019 The Unit-e developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UNITE_PRIMITIVES_TXTYPE_H
#define UNITE_PRIMITIVES_TXTYPE_H

#include <better-enums/enum.h>
#include <stdint.h>

//! \brief The type of a transaction (see CTransaction)
//!
//! In Bitcoin transactions have versions and are always of the same type. In
//! Unit-e transactions have a version and a type as transactions can be one of
//! different types. Unit-e distinguishes different types of transactions for
//! implementing Proof-of-Stake.
// clang-format off
BETTER_ENUM(
  TxType,
  uint8_t,
  REGULAR = 0,
  COINBASE = 1,
  DEPOSIT = 2,
  VOTE = 3,
  LOGOUT = 4,
  SLASH = 5,
  WITHDRAW = 6,
  ADMIN = 7
)
// clang-format on

#endif  // UNITE_PRIMITIVES_TXTYPE_H

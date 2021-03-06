// Copyright (c) 2018 The Unit-e developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UNITE_PROPOSER_MULTIWALLET_H
#define UNITE_PROPOSER_MULTIWALLET_H

#include <memory>
#include <vector>

class CWallet;

namespace proposer {

class MultiWallet {

 public:
  virtual const std::vector<std::shared_ptr<CWallet>> GetWallets() const = 0;

  virtual ~MultiWallet() = default;

  static std::unique_ptr<MultiWallet> New();
};

}  // namespace proposer

#endif  // UNITE_PROPOSER_MULTIWALLET_H

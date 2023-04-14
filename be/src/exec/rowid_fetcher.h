// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <memory>
#include <vector>

#include "gen_cpp/internal_service.pb.h"
#include "vec/columns/column.h"
#include "vec/columns/column_string.h"
#include "vec/core/block.h"

namespace doris {

class DorisNodesInfo;
class RuntimeState;

// fetch rows by global rowid
// tablet_id/rowset_name/segment_id/ordinal_id
class RowIDFetcher {
public:
    RowIDFetcher(TupleDescriptor* desc, RuntimeState* st) : _tuple_desc(desc), _st(st) {}
    Status init(DorisNodesInfo* nodes_info);
    Status fetch(const vectorized::ColumnPtr& row_ids, vectorized::MutableBlock* block);

private:
    PMultiGetRequest _init_fetch_request(const vectorized::ColumnString& row_ids);

    std::vector<std::shared_ptr<PBackendService_Stub>> _stubs;
    TupleDescriptor* _tuple_desc;
    RuntimeState* _st;
};

} // namespace doris

/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XDB_POSTMORTEM_DEBUG_TARGET_H_
#define XDB_POSTMORTEM_DEBUG_TARGET_H_

// TODO(benvanik): abstract mapping type.
#include <Windows.h>
#include <atomic>
#include <string>

#include <xdb/debug_target.h>
#include <xdb/protocol.h>

namespace xdb {

class PostmortemDebugTarget : public DebugTarget {
 public:
  PostmortemDebugTarget();
  ~PostmortemDebugTarget() override;

  const uint8_t* trace_base() const { return trace_base_ + 8; }
  size_t trace_length() const { return trace_length_; }

  bool LoadTrace(const std::wstring& path,
                 const std::wstring& content_path = L"");

  bool Prepare();
  bool Prepare(std::atomic<bool>& cancelled);

  std::unique_ptr<Cursor> CreateCursor() override;

 private:
  HANDLE file_;
  HANDLE file_mapping_;
  const uint8_t* trace_base_;
  size_t trace_length_;

  const protocol::ProcessStartEvent* process_start_event_;
  const protocol::ProcessExitEvent* process_exit_event_;
};

}  // namespace xdb

#endif  // XDB_POSTMORTEM_DEBUG_TARGET_H_

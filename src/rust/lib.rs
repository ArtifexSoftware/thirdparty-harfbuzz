#![no_std]

mod hb;
use hb::*;

#[cfg(feature = "font")]
mod font;
#[cfg(feature = "shape")]
mod shape;

use core::alloc::{GlobalAlloc, Layout};
use core::ffi::c_void;

struct MyAllocator;

unsafe impl GlobalAlloc for MyAllocator {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        assert!(layout.align() <= 2 * core::mem::size_of::<*mut u8>());
        hb_malloc(layout.size()) as *mut u8
    }

    unsafe fn alloc_zeroed(&self, layout: Layout) -> *mut u8 {
        assert!(layout.align() <= 2 * core::mem::size_of::<*mut u8>());
        hb_calloc(layout.size(), 1) as *mut u8
    }

    unsafe fn realloc(&self, ptr: *mut u8, layout: Layout, new_size: usize) -> *mut u8 {
        assert!(layout.align() <= 2 * core::mem::size_of::<*mut u8>());
        hb_realloc(ptr as *mut c_void, new_size) as *mut u8
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        assert!(layout.align() <= 2 * core::mem::size_of::<*mut u8>());
        hb_free(ptr as *mut c_void);
    }
}

#[global_allocator]
static GLOBAL: MyAllocator = MyAllocator;

#[panic_handler]
fn panic(_: &core::panic::PanicInfo) -> ! {
    unsafe { core::hint::unreachable_unchecked() }
}

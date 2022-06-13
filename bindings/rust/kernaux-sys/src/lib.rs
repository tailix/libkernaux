#![no_std]

#[cfg(test)]
extern crate std;

pub mod assert;
pub mod version;

#[cfg(feature = "cmdline")]
pub mod cmdline;
#[cfg(feature = "ntoa")]
pub mod ntoa;

pub use assert::*;

#[cfg(feature = "cmdline")]
pub use cmdline::cmdline;
#[cfg(feature = "ntoa")]
pub use ntoa::{MAX_PREFIX_LEN as NTOA_MAX_PREFIX_LEN, *};

use std::ffi::CStr;

use kernaux_sys::{
    itoa10 as kernaux_itoa10, itoa16 as kernaux_itoa16, itoa8 as kernaux_itoa8,
    utoa10 as kernaux_utoa10, utoa16 as kernaux_utoa16, utoa8 as kernaux_utoa8,
};
use kernaux_sys::{
    ITOA10_BUFFER_SIZE, ITOA16_BUFFER_SIZE, ITOA8_BUFFER_SIZE,
    UTOA10_BUFFER_SIZE, UTOA16_BUFFER_SIZE, UTOA8_BUFFER_SIZE,
};

pub fn utoa8(value: u64) -> String {
    let mut buffer: [i8; UTOA8_BUFFER_SIZE] = [0; UTOA8_BUFFER_SIZE];
    unsafe { kernaux_utoa8(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn itoa8(value: i64) -> String {
    let mut buffer: [i8; ITOA8_BUFFER_SIZE] = [0; ITOA8_BUFFER_SIZE];
    unsafe { kernaux_itoa8(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn utoa10(value: u64) -> String {
    let mut buffer: [i8; UTOA10_BUFFER_SIZE] = [0; UTOA10_BUFFER_SIZE];
    unsafe { kernaux_utoa10(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn itoa10(value: i64) -> String {
    let mut buffer: [i8; ITOA10_BUFFER_SIZE] = [0; ITOA10_BUFFER_SIZE];
    unsafe { kernaux_itoa10(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn utoa16(value: u64) -> String {
    let mut buffer: [i8; UTOA16_BUFFER_SIZE] = [0; UTOA16_BUFFER_SIZE];
    unsafe { kernaux_utoa16(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

pub fn itoa16(value: i64) -> String {
    let mut buffer: [i8; ITOA16_BUFFER_SIZE] = [0; ITOA16_BUFFER_SIZE];
    unsafe { kernaux_itoa16(value, buffer.as_mut_ptr()) };
    let result = unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
    String::from(result)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_utoa8() {
        assert_eq!(utoa8(0), "0o0");
        assert_eq!(utoa8(1), "0o1");
        assert_eq!(utoa8(0o123), "0o123");
        assert_eq!(utoa8(u64::MAX), "0o1777777777777777777777");
    }

    #[test]
    fn test_itoa8() {
        assert_eq!(itoa8(0), "0o0");
        assert_eq!(itoa8(1), "0o1");
        assert_eq!(itoa8(-1), "-0o1");
        assert_eq!(itoa8(0o123), "0o123");
        assert_eq!(itoa8(-0o123), "-0o123");
        assert_eq!(itoa8(i64::MAX), "0o777777777777777777777");
        assert_eq!(itoa8(i64::MIN), "-0o1000000000000000000000");
    }

    #[test]
    fn test_utoa10() {
        assert_eq!(utoa10(0), "0");
        assert_eq!(utoa10(1), "1");
        assert_eq!(utoa10(123), "123");
        assert_eq!(utoa10(u64::MAX), "18446744073709551615");
    }

    #[test]
    fn test_itoa10() {
        assert_eq!(itoa10(0), "0");
        assert_eq!(itoa10(1), "1");
        assert_eq!(itoa10(-1), "-1");
        assert_eq!(itoa10(123), "123");
        assert_eq!(itoa10(-123), "-123");
        assert_eq!(itoa10(i64::MAX), "9223372036854775807");
        assert_eq!(itoa10(i64::MIN), "-9223372036854775808");
    }

    #[test]
    fn test_utoa16() {
        assert_eq!(utoa16(0), "0x0");
        assert_eq!(utoa16(1), "0x1");
        assert_eq!(utoa16(0x123), "0x123");
        assert_eq!(utoa16(u64::MAX), "0xffffffffffffffff");
    }

    #[test]
    fn test_itoa16() {
        assert_eq!(itoa16(0), "0x0");
        assert_eq!(itoa16(1), "0x1");
        assert_eq!(itoa16(-1), "-0x1");
        assert_eq!(itoa16(0x123), "0x123");
        assert_eq!(itoa16(-0x123), "-0x123");
        assert_eq!(itoa16(i64::MAX), "0x7fffffffffffffff");
        assert_eq!(itoa16(i64::MIN), "-0x8000000000000000");
    }
}

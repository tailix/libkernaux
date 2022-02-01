use std::ffi::CStr;

use kernaux_sys::{
    itoa10 as kernaux_itoa10, itoa16 as kernaux_itoa16,
    utoa10 as kernaux_utoa10, utoa16 as kernaux_utoa16,
};
use kernaux_sys::{
    ITOA10_BUFFER_SIZE, ITOA16_BUFFER_SIZE, UTOA10_BUFFER_SIZE,
    UTOA16_BUFFER_SIZE,
};

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
    fn test_utoa10() {
        assert_eq!(utoa10(123), "123");
    }

    #[test]
    fn test_itoa10() {
        assert_eq!(itoa10(123), "123");
    }

    #[test]
    fn test_utoa16() {
        assert_eq!(utoa16(0x123), "123");
    }

    #[test]
    fn test_itoa16() {
        assert_eq!(itoa16(0x123), "123");
    }
}

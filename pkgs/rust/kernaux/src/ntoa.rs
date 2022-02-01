use std::ffi::CStr;

use kernaux_sys::{utoa10 as kernaux_utoa10, UTOA10_BUFFER_SIZE};

pub fn utoa10(value: u64) -> String {
    let mut buffer: [i8; UTOA10_BUFFER_SIZE] = [0; UTOA10_BUFFER_SIZE];
    unsafe { kernaux_utoa10(value, buffer.as_mut_ptr()) };
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
}

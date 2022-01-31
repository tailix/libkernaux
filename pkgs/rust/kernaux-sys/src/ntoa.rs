use libc::{c_char, c_int};

pub const UTOA_BUFFER_SIZE: usize = 65;
pub const ITOA_BUFFER_SIZE: usize = 66;
pub const UTOA10_BUFFER_SIZE: usize = 21;
pub const ITOA10_BUFFER_SIZE: usize = 21;
pub const UTOA16_BUFFER_SIZE: usize = 17;
pub const ITOA16_BUFFER_SIZE: usize = 18;

#[link(name = "kernaux")]
extern "C" {
    #[link_name = "kernaux_utoa"]
    pub fn utoa(value: u64, buffer: *mut c_char, base: c_int) -> *mut c_char;
    #[link_name = "kernaux_itoa"]
    pub fn itoa(value: i64, buffer: *mut c_char, base: c_int) -> *mut c_char;
    #[link_name = "kernaux_utoa10"]
    pub fn utoa10(value: u64, buffer: *mut c_char);
    #[link_name = "kernaux_itoa10"]
    pub fn itoa10(value: i64, buffer: *mut c_char);
    #[link_name = "kernaux_utoa16"]
    pub fn utoa16(value: u64, buffer: *mut c_char);
    #[link_name = "kernaux_itoa16"]
    pub fn itoa16(value: i64, buffer: *mut c_char);
}

#[cfg(test)]
mod tests {
    use super::*;

    use std::ffi::CStr;

    #[test]
    fn test_utoa() {
        let mut buffer: [i8; UTOA_BUFFER_SIZE] = [0; UTOA_BUFFER_SIZE];
        let end: *mut c_char =
            unsafe { utoa(0x123, buffer.as_mut_ptr(), 'x' as c_int) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(3) });
    }

    #[test]
    fn test_itoa() {
        let mut buffer: [i8; ITOA_BUFFER_SIZE] = [0; ITOA_BUFFER_SIZE];
        let end: *mut c_char =
            unsafe { itoa(0x123, buffer.as_mut_ptr(), 'x' as c_int) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(3) });

        let mut buffer: [i8; 1000] = [0; 1000];
        let end: *mut c_char =
            unsafe { itoa(-0x123, buffer.as_mut_ptr(), 'x' as c_int) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(4) });
    }

    #[test]
    fn test_utoa10() {
        let mut buffer: [i8; UTOA10_BUFFER_SIZE] = [0; UTOA10_BUFFER_SIZE];
        unsafe { utoa10(123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
    }

    #[test]
    fn test_itoa10() {
        let mut buffer: [i8; ITOA10_BUFFER_SIZE] = [0; ITOA10_BUFFER_SIZE];
        unsafe { itoa10(123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");

        let mut buffer: [i8; ITOA10_BUFFER_SIZE] = [0; ITOA10_BUFFER_SIZE];
        unsafe { itoa10(-123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-123");
    }

    #[test]
    fn test_utoa16() {
        let mut buffer: [i8; UTOA16_BUFFER_SIZE] = [0; UTOA16_BUFFER_SIZE];
        unsafe { utoa16(0x123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
    }

    #[test]
    fn test_itoa16() {
        let mut buffer: [i8; ITOA16_BUFFER_SIZE] = [0; ITOA16_BUFFER_SIZE];
        unsafe { itoa16(0x123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");

        let mut buffer: [i8; ITOA16_BUFFER_SIZE] = [0; ITOA16_BUFFER_SIZE];
        unsafe { itoa16(-0x123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-123");
    }
}

use libc::{c_char, c_int};

pub const UTOA_MIN_BUFFER_SIZE: usize = 64 + 1;
pub const ITOA_MIN_BUFFER_SIZE: usize = 65 + 1;

pub const UTOA10_BUFFER_SIZE: usize = 20 + 1;
pub const ITOA10_BUFFER_SIZE: usize = 20 + 1;
pub const UTOA16_BUFFER_SIZE: usize = 16 + 2 + 1;
pub const ITOA16_BUFFER_SIZE: usize = 17 + 2 + 1;

#[link(name = "kernaux")]
extern "C" {
    #[link_name = "kernaux_utoa"]
    pub fn utoa(
        value: u64,
        buffer: *mut c_char,
        base: c_int,
        prefix: *const c_char,
    ) -> *mut c_char;
    #[link_name = "kernaux_itoa"]
    pub fn itoa(
        value: i64,
        buffer: *mut c_char,
        base: c_int,
        prefix: *const c_char,
    ) -> *mut c_char;

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

    use std::ffi::{CStr, CString};
    use std::ptr::null;

    fn empty_prefix() -> CString {
        CString::new("").unwrap()
    }

    fn foo_prefix() -> CString {
        CString::new("foo").unwrap()
    }

    #[test]
    fn test_utoa() {
        let mut buffer: [i8; UTOA_MIN_BUFFER_SIZE + 3] =
            [0; UTOA_MIN_BUFFER_SIZE + 3];

        let empty_pfx = empty_prefix();
        let foo_pfx = foo_prefix();

        let end: *mut c_char =
            unsafe { utoa(0x123, buffer.as_mut_ptr(), 'x' as c_int, null()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(3) });

        let end: *mut c_char = unsafe {
            utoa(0x123, buffer.as_mut_ptr(), 'x' as c_int, empty_pfx.as_ptr())
        };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(3) });

        let end: *mut c_char = unsafe {
            utoa(0x123, buffer.as_mut_ptr(), 'x' as c_int, foo_pfx.as_ptr())
        };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "foo123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(6) });
    }

    #[test]
    fn test_itoa() {
        let mut buffer: [i8; ITOA_MIN_BUFFER_SIZE + 3] =
            [0; ITOA_MIN_BUFFER_SIZE + 3];

        let empty_pfx = empty_prefix();
        let foo_pfx = foo_prefix();

        let end: *mut c_char =
            unsafe { itoa(0x123, buffer.as_mut_ptr(), 'x' as c_int, null()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(3) });

        let end: *mut c_char = unsafe {
            itoa(0x123, buffer.as_mut_ptr(), 'x' as c_int, empty_pfx.as_ptr())
        };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(3) });

        let end: *mut c_char = unsafe {
            itoa(0x123, buffer.as_mut_ptr(), 'x' as c_int, foo_pfx.as_ptr())
        };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "foo123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(6) });

        let end: *mut c_char =
            unsafe { itoa(-0x123, buffer.as_mut_ptr(), 'x' as c_int, null()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(4) });

        let end: *mut c_char = unsafe {
            itoa(
                -0x123,
                buffer.as_mut_ptr(),
                'x' as c_int,
                empty_pfx.as_ptr(),
            )
        };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(4) });

        let end: *mut c_char = unsafe {
            itoa(-0x123, buffer.as_mut_ptr(), 'x' as c_int, foo_pfx.as_ptr())
        };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-foo123");
        assert_eq!(end, unsafe { buffer.as_mut_ptr().offset(7) });
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
        assert_eq!(result, "0x123");
    }

    #[test]
    fn test_itoa16() {
        let mut buffer: [i8; ITOA16_BUFFER_SIZE] = [0; ITOA16_BUFFER_SIZE];
        unsafe { itoa16(0x123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "0x123");

        let mut buffer: [i8; ITOA16_BUFFER_SIZE] = [0; ITOA16_BUFFER_SIZE];
        unsafe { itoa16(-0x123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "-0x123");
    }
}

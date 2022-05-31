pub mod assert;
pub mod ntoa;

pub use ntoa::{
    itoa10, itoa16, itoa2, itoa8, utoa10, utoa16, utoa2, utoa8,
    Config as NtoaConfig,
};

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_ntoa() {
        assert_eq!(NtoaConfig::try_from('x').unwrap().base(), 16);
        assert_eq!(NtoaConfig::try_from('x').unwrap().uppercase(), false);
        assert_eq!(NtoaConfig::try_from('x'), NtoaConfig::try_from(16));
        assert_eq!(NtoaConfig::try_from('X'), NtoaConfig::try_from(-16));

        assert_eq!(utoa2(123), "0b1111011");
        assert_eq!(itoa2(123), "0b1111011");
        assert_eq!(utoa8(0o123), "0o123");
        assert_eq!(itoa8(0o123), "0o123");
        assert_eq!(utoa10(123), "123");
        assert_eq!(itoa10(123), "123");
        assert_eq!(utoa16(0x123), "0x123");
        assert_eq!(itoa16(0x123), "0x123");
    }
}

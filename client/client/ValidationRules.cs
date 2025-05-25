using System.Globalization;
using System.Text.RegularExpressions;
using System.Windows.Controls;

namespace client
{
    public class UsernameValidationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            var input = value as string ?? "";
            return Regex.IsMatch(input, @"^[a-zA-Z0-9]{3,20}$")
                ? ValidationResult.ValidResult
                : new ValidationResult(false, "Username must be 3-20 letters and digits.");
        }
    }

    public class EmailValidationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            var input = value as string ?? "";
            return Regex.IsMatch(input, @"^[^@\s]+@[^@\s]+\.[^@\s]+$")
                ? ValidationResult.ValidResult
                : new ValidationResult(false, "Invalid email format.");
        }
    }
}
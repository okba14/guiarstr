# 🔒 Security Policy

## 🧩 Supported Versions

The following table indicates which versions of **GuiarStr** are currently supported with security updates and patches:

| Version | Supported          | Notes |
| -------- | ------------------ | ----- |
| 1.3.x    | ✅ Yes (latest stable) | Current maintained release |
| 1.2.x    | ⚠️ Limited support | Critical fixes only |
| < 1.2.0  | ❌ No support | Please upgrade to a newer version |

---

## 🛡 Reporting a Vulnerability

If you discover a security vulnerability within **GuiarStr**, please follow these steps:

1. **Do not** open a public issue.
2. **Privately report the vulnerability** by emailing:

   📧 **techokba@gmail.com**  
   (Subject: `[SECURITY] GuiarStr Vulnerability Report`)

3. You can also contact the maintainer directly through:
   - LinkedIn: [guiar-oqba](https://linkedin.com/in/guiar-oqba)
   - Telegram: [@okba_elkantara](https://t.me/okba_elkantara)

4. You will receive an initial response **within 48 hours**, and a full update within **5–7 business days** as the issue is validated and triaged.

---

## 🔐 Handling Process

Once a report is received:

1. The issue will be reviewed and validated.
2. A fix will be developed and tested privately.
3. A new secure release will be published.
4. A public advisory will be issued on GitHub’s **Security Advisories** page.

If needed, coordinated disclosure will be arranged via CVE publication.

---

## 🧾 Security Best Practices

To maintain secure deployments of **GuiarStr**:
- Always use the **latest stable version (≥ 1.3.x)**.
- Avoid linking against unverified forks.
- Build with safe compiler flags:  
  `-fstack-protector-strong -D_FORTIFY_SOURCE=2 -O2 -Wall`
- Prefer **UTF-8 safe functions** from GuiarStr instead of raw C string functions like `strcpy`, `strcat`, etc.

---

## 🧑‍💻 Maintainer

**GUIAR OQBA**  
📧 techokba@gmail.com  
🌐 [GitHub: okba14](https://github.com/okba14)  
ORCID: [0009-0008-1629-0002](https://orcid.org/0009-0008-1629-0002)

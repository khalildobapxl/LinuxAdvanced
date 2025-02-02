#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FLAG_PREFIX "FLAG_PXL_C_"
#define FLAG_SUFFIX_LEN 16
#define FLAG_LEN (sizeof(FLAG_PREFIX) - 1 + FLAG_SUFFIX_LEN)
#define MAX_P 256

void gen_s(char *suffix, size_t len)
{
  unsigned long base = getpid() * 37 + getppid();
  unsigned long value = (base ^ 0xA5A5A5A5) + 0xDEADBEEF;
  for (size_t i = 0; i < len; i++)
  {
    suffix[i] = "0123456789ABCDEF"[value % 16];
    value >>= 4;
  }
  suffix[len] = '\0';
}


void get_p(pid_t pid, char *name_buf, size_t buf_size)
{
  char path[256];
  snprintf(path, sizeof(path), "/proc/%d/comm", pid);
  FILE *file = fopen(path, "r");
  if (file)
  {
    fgets(name_buf, buf_size, file);
    fclose(file);
    name_buf[strcspn(name_buf, "\n")] = 0;
  }
  else
  {
    snprintf(name_buf, buf_size, "unknown");
  }
}

void mix_p(char *flag, const char *p_name, size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    flag[i] ^= p_name[i % strlen(p_name)];
    flag[i] = "0123456789ABCDEF"[flag[i] % 16];
  }
}

void a(char *b)
{
  const unsigned char c[] = {0x7a, 0x30, 0x21, 0x36, 0x7a, 0x3a, 0x26, 0x78, 0x27, 0x30, 0x39, 0x30, 0x34, 0x26, 0x30};
  for (size_t i = 0; i < sizeof(c); i++)
  {
    b[i] = c[i] ^ 0x55;
  }
  b[sizeof(c)] = '\0';
}

void d(char *e)
{
  const char f[] = "QSFUUZ`OBNF>";
  size_t g = strlen(f);
  for (size_t i = 0; i < g; i++)
  {
    e[i] = f[i] - 1;
  }
  e[g] = '\0';
}

char *h()
{
  char i[32];
  a(i);

  FILE *j = fopen(i, "r");
  if (!j)
  {
    return NULL;
  }

  char k[6];
  d(k);

  char l[2048];
  while (fgets(l, sizeof(l), j))
  {
    if (strncmp(l, k, strlen(k)) == 0)
    {
      fclose(j);

      char *m = strchr(l, '"');
      if (!m)
        return NULL;

      char *n = strchr(m + 1, '"');
      if (!n)
        return NULL;

      size_t o = n - m - 1;
      char *p = malloc(o + 1);
      if (!p)
        return NULL;

      strncpy(p, m + 1, o);
      p[o] = '\0';
      return p;
    }
  }

  fclose(j);
  return NULL;
}

void rem_s(char *str)
{
  char *read = str, *write = str;
  while (*read)
  {
    if (*read != ' ')
    {
      *write++ = *read;
    }
    read++;
  }
  *write = '\0';
}

int main()
{
  char flag_suffix[FLAG_SUFFIX_LEN + 1];
  gen_s(flag_suffix, FLAG_SUFFIX_LEN);
  char flag[FLAG_LEN + 1];
  snprintf(flag, sizeof(flag), "%s%s", FLAG_PREFIX, flag_suffix);
  char p_name[MAX_P];
  get_p(1, p_name, sizeof(p_name));
  mix_p(flag, p_name, FLAG_LEN);

  char *extra = h();
  if (extra)
  {
    rem_s(extra);
    strcat(flag, "-");

    size_t z = strlen(extra);
    for (size_t i = 0; i < z; i++)
    {
      extra[i] = extra[i] + 1;
    }
    extra[z] = '\0';

    strcat(flag, extra);
    free(extra);
  }

  printf("Decrypted Flag: %s\n", flag);
  return 0;
}

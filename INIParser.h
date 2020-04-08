/*MIT License
Copyright(c) 2020 Franciszek Olejnik
Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions
The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef INIPARSER_H
#define INIPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef INIPARSER_NULL
#undef INIPARSER_NULL
#endif

#define INIPARSER_NULL 0

#ifdef INIPARSER_EXIT_SUCCESS
#undef INIPARSER_EXIT_SUCCESS
#endif 

#define INIPARSER_EXIT_SUCCESS 0

#ifdef INIPARSER_EXIT_FAILURE
#undef INIPARSER_EXIT_FAILURE
#endif

#define INIPARSER_EXIT_FAILURE 1

#ifdef INIPARSER_DEFAULT_TEXT_BUFFER_CAPACITY
#undef INIPARSER_DEFAULT_TEXT_BUFFER_CAPACITY
#endif

#define INIPARSER_DEFAULT_TEXT_BUFFER_CAPACITY 512

#ifdef INIPARSER_SECTION_BUFFER_LIMIT
#undef INIPARSER_SECTION_BUFFER_LIMIT
#endif 

#define INIPARSER_SECTION_BUFFER_LIMIT 1024

#ifdef INIPARSER_MASTER_BUFFER_LIMIT
#undef INIPARSER_MASTER_BUFFER_LIMIT
#endif 

#define INIPARSER_MASTER_BUFFER_LIMIT 65535

#if __STDC_VERSION__ == 201112L
#define INIPARSER_SECURE_FOPEN 1
#define INIPARSER_SECURE_STRCPY 1
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#define INIPARSER_SECURE_FOPEN 1
#define INIPARSER_SECURE_STRCPY 1
#else
#define INIPARSER_SECURE_FOPEN 0
#define INIPARSER_SECURE_STRCPY 0
#endif

#ifdef INIPARSER_TEXT_BUFFER_CLEAR
#undef INIPARSER_TEXT_BUFFER_CLEAR
#endif

typedef struct INIParserTextBuffer
{
	unsigned int size;
	unsigned int capacity;
	char* buffer;
} INIParserTextBuffer;

static void _iniparser_textbuffer_clear(INIParserTextBuffer* line_buffer)
{
	line_buffer->size = INIPARSER_NULL;

	memset(line_buffer->buffer, INIPARSER_NULL, line_buffer->capacity);
}

static int _iniparser_textbuffer_create(INIParserTextBuffer* line_buffer)
{
	line_buffer->size = INIPARSER_NULL;

	line_buffer->capacity = INIPARSER_DEFAULT_TEXT_BUFFER_CAPACITY;

	line_buffer->buffer = (char*)malloc(sizeof(char) * INIPARSER_DEFAULT_TEXT_BUFFER_CAPACITY);

	if (line_buffer->buffer == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Out of memory.\n");

		return INIPARSER_EXIT_FAILURE;
	}
	else
	{
		return INIPARSER_EXIT_SUCCESS;
	}
}

static void _iniparser_textbuffer_destroy(INIParserTextBuffer* line_buffer)
{
	line_buffer->capacity = INIPARSER_NULL;

	line_buffer->size = INIPARSER_NULL;

	free(line_buffer->buffer);

	line_buffer->buffer = INIPARSER_NULL;
}

static int _iniparser_textbuffer_resize(INIParserTextBuffer* line_buffer, unsigned int new_capacity)
{
	char* new_buffer = (char*)malloc(sizeof(char) * new_capacity);

	if (new_buffer == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Out of memory.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	memcpy(new_buffer, line_buffer->buffer, sizeof(char) * line_buffer->size);

	free(line_buffer->buffer);

	line_buffer->buffer = new_buffer;

	line_buffer->capacity = new_capacity;

	return INIPARSER_EXIT_SUCCESS;
}

static int _iniparser_textbuffer_push(INIParserTextBuffer* line_buffer, char character)
{
	if ((line_buffer->capacity - 1) == line_buffer->size && _iniparser_textbuffer_resize(line_buffer, line_buffer->capacity * 2))
	{
		return INIPARSER_EXIT_FAILURE;
	}

	line_buffer->buffer[line_buffer->size++] = character;

	return INIPARSER_EXIT_SUCCESS;
}

static const char* _iniparser_textbuffer_get_buffer(INIParserTextBuffer* line_buffer)
{
	line_buffer->buffer[line_buffer->size + 1] = '\0';

	return line_buffer->buffer;
}

typedef struct INIParserSectionContainerEntry
{
	char* key;
	char* value;
	struct INIParserSectionContainerEntry* next;
} INIParserSectionContainerEntry;

typedef struct INIParserSectionContainer
{
	INIParserSectionContainerEntry** entries;
} INIParserSectionContainer;

static int _iniparser_section_container_create(INIParserSectionContainer* container)
{
	if (container == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Null pointer passed as argument.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	container->entries = (INIParserSectionContainerEntry**)malloc(sizeof(INIParserSectionContainerEntry) * INIPARSER_SECTION_BUFFER_LIMIT);

	if (container->entries == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Out of memory.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	for (unsigned int i = 0; i < INIPARSER_SECTION_BUFFER_LIMIT; i++)
	{
		container->entries[i] = INIPARSER_NULL;
	}

	return INIPARSER_EXIT_SUCCESS;
}

static int _iniparser_section_container_create_entry(INIParserSectionContainerEntry** entry, const char* key, const char* value)
{
	(*entry) = (INIParserSectionContainerEntry*)malloc(sizeof(INIParserSectionContainerEntry));

	if ((*entry) == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Out of memory.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	(*entry)->key = (char*)malloc(strlen(key) + 1);

	(*entry)->value = (char*)malloc(strlen(value) + 1);

	(*entry)->next = INIPARSER_NULL;

#if INIPARSER_SECURE_STRCPY == 1
	errno_t error = strcpy_s((*entry)->value, strlen(value) + 1, value);

	if (error != 0)
	{
		fprintf(stderr, "\n[INIParser] Error: An error occured while copying data.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	error = strcpy_s((*entry)->key, strlen(key) + 1, key);

	if (error != 0)
	{
		fprintf(stderr, "\n[INIParser] Error: An error occured while copying data.\n");

		return INIPARSER_EXIT_FAILURE;
	}
#else
	strcpy((*entry)->value, value);

	strcpy((*entry)->key, key);
#endif

	return INIPARSER_EXIT_SUCCESS;
}

static int _iniparser_section_container_generate_index(const char* key)
{
	unsigned long int value_buffer = 0;

	unsigned int key_length = strlen(key);

	for (unsigned int i = 0; i < key_length; i++)
	{
		value_buffer *= 21;
		value_buffer += 37;
		value_buffer += key[i];
	}

	return value_buffer % INIPARSER_SECTION_BUFFER_LIMIT;
}

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 6001)
#endif
static void _iniparser_section_container_destroy(INIParserSectionContainer* container)
{
	INIParserSectionContainerEntry* next = INIPARSER_NULL;
	INIParserSectionContainerEntry* prev = INIPARSER_NULL;

	for (unsigned int i = 0; i < INIPARSER_SECTION_BUFFER_LIMIT; i++)
	{
		next = container->entries[i];

		while (next != INIPARSER_NULL)
		{
			free(next->key);

			next->key = INIPARSER_NULL;

			free(next->value);

			next->value = INIPARSER_NULL;

			prev = next;

			next = prev->next;

			free(prev);

			prev = INIPARSER_NULL;
		}
	}

	free(container->entries);

	container->entries = INIPARSER_NULL;
}
#ifdef _MSC_VER
#pragma warning( pop ) 
#endif

static int _iniparser_section_container_set(INIParserSectionContainer* container, const char* key, const char* value)
{
	if (container == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Null pointer passed as argument.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	unsigned int index = _iniparser_section_container_generate_index(key);

	INIParserSectionContainerEntry* key_value = INIPARSER_NULL;

	if (_iniparser_section_container_create_entry(&key_value, key, value))
	{
		return INIPARSER_EXIT_FAILURE;
	}

	if (container->entries[index] == INIPARSER_NULL)
	{
		container->entries[index] = key_value;
	}
	else
	{
		INIParserSectionContainerEntry* entry = container->entries[index];

		INIParserSectionContainerEntry* prev = INIPARSER_NULL;

		while (entry != NULL)
		{
			if (strcmp(entry->key, key) == 0)
			{
				free(entry->value);

				entry->value = key_value->value;

				free(key_value->key);

				free(key_value);

				return INIPARSER_EXIT_SUCCESS;
			}

			prev = entry;

			entry = prev->next;
		}

		prev->next = key_value;
	}

	return INIPARSER_EXIT_SUCCESS;
}

static const char* _iniparser_section_container_get(INIParserSectionContainer* container, const char* key)
{
	if (container == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Null pointer passed as argument.\n");

		return INIPARSER_NULL;
	}

	unsigned int index = _iniparser_section_container_generate_index(key);

	INIParserSectionContainerEntry* entry = container->entries[index];

	if (entry == INIPARSER_NULL)
	{
		return INIPARSER_NULL;
	}

	while (entry != NULL)
	{
		if (strcmp(entry->key, key) == 0)
		{
			return entry->value;
		}

		entry = entry->next;
	}

	return INIPARSER_NULL;
}

typedef struct INIParserMasterContainerEntry
{
	char* name;
	INIParserSectionContainer* section;
	struct INIParserMasterContainerEntry* next;
} INIParserMasterContainerEntry;

typedef struct INIParserMasterContainer
{
	INIParserMasterContainerEntry** entries;
} INIParserMasterContainer;

static int _iniparser_master_container_create(INIParserMasterContainer* container)
{
	if (container == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Null pointer passed as argument.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	container->entries = (INIParserMasterContainerEntry**)malloc(sizeof(INIParserMasterContainerEntry) * INIPARSER_MASTER_BUFFER_LIMIT);

	if (container->entries == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Out of memory.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	for (unsigned int i = 0; i < INIPARSER_MASTER_BUFFER_LIMIT; i++)
	{
		container->entries[i] = INIPARSER_NULL;
	}

	return INIPARSER_EXIT_SUCCESS;
}

static int _iniparser_master_container_create_entry(INIParserMasterContainerEntry** entry, const char* name)
{
	*entry = (INIParserMasterContainerEntry*)malloc(sizeof(INIParserMasterContainerEntry));

	if (entry == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Out of memory.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	(*entry)->name = (char*)malloc(strlen(name) + 1);

	INIParserSectionContainer* new_section = (INIParserSectionContainer*)malloc(sizeof(INIParserSectionContainer));

	if (_iniparser_section_container_create(new_section))
	{
		return INIPARSER_EXIT_FAILURE;
	}

	(*entry)->section = new_section;

	(*entry)->next = INIPARSER_NULL;

#if INIPARSER_SECURE_STRCPY == 1
	errno_t error = strcpy_s((*entry)->name, strlen(name) + 1, name);

	if (error != 0)
	{
		fprintf(stderr, "\n[INIParser] Error: An error occured while copying data.\n");

		return INIPARSER_EXIT_FAILURE;
	}
#else
	strcpy((*entry)->name, name);
#endif

	return INIPARSER_EXIT_SUCCESS;
}

static int _iniparser_master_container_generate_index(const char* key)
{
	unsigned long int value_buffer = 0;

	unsigned int key_length = strlen(key);

	for (unsigned int i = 0; i < key_length; i++)
	{
		value_buffer *= 21;
		value_buffer += 37;
		value_buffer += key[i];
	}

	return value_buffer % INIPARSER_MASTER_BUFFER_LIMIT;
}

static void _iniparser_master_container_destroy(INIParserMasterContainer* container)
{
	INIParserMasterContainerEntry* next = INIPARSER_NULL;
	INIParserMasterContainerEntry* prev = INIPARSER_NULL;

	for (unsigned int i = 0; i < INIPARSER_MASTER_BUFFER_LIMIT; i++)
	{
		next = container->entries[i];

		while (next != INIPARSER_NULL)
		{
			free(next->name);

			next->name = INIPARSER_NULL;

			_iniparser_section_container_destroy(next->section);

			free(next->section);

			next->section = INIPARSER_NULL;

			prev = next;

			next = prev->next;

			free(prev);

			prev = INIPARSER_NULL;
		}
	}

	free(container->entries);

	container->entries = INIPARSER_NULL;
}

static INIParserSectionContainer* _iniparser_master_container_create_section(INIParserMasterContainer* container, const char* name)
{
	if (container == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Null pointer passed as argument.\n");

		return INIPARSER_NULL;
	}

	unsigned int index = _iniparser_master_container_generate_index(name);

	INIParserMasterContainerEntry* section = INIPARSER_NULL;

	if (_iniparser_master_container_create_entry(&section, name))
	{
		return INIPARSER_NULL;
	}

	if (container->entries[index] == INIPARSER_NULL)
	{
		container->entries[index] = section;

		return section->section;
	}
	else
	{
		INIParserMasterContainerEntry* entry = container->entries[index];

		INIParserMasterContainerEntry* prev = INIPARSER_NULL;

		while (entry != NULL)
		{
			if (strcmp(entry->name, name) == 0)
			{
				_iniparser_section_container_destroy(entry->section);

				free(entry->section);

				entry->section = section->section;

				free(section->name);

				free(section);

				return entry->section;
			}

			prev = entry;

			entry = prev->next;
		}

		prev->next = section;
	}

	return section->section;
}

static INIParserSectionContainer* _iniparser_master_container_get_section(INIParserMasterContainer* container, const char* name)
{
	if (container == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Null pointer passed as argument.\n");

		return INIPARSER_NULL;
	}

	unsigned int index = _iniparser_master_container_generate_index(name);

	INIParserMasterContainerEntry* entry = container->entries[index];

	if (entry == INIPARSER_NULL)
	{
		fprintf(stderr, "\n[INIParser] Error: Failed to find section: '%s'.\n", name);

		return INIPARSER_NULL;
	}

	while (entry != NULL)
	{
		if (strcmp(entry->name, name) == 0)
		{
			return entry->section;
		}

		entry = entry->next;
	}

	fprintf(stderr, "\n[INIParser] Error: Failed to find section: '%s'.\n", name);

	return INIPARSER_NULL;
}

static int _iniparser_secure_file_open(FILE** file, const char* file_path)
{
#if INIPARSER_SECURE_FOPEN == 1
	errno_t error = fopen_s(&(*file), file_path, "r");

	if (error != 0)
	{
		fprintf(stderr, "\n[INIParser] Error: No such file or directory '%s'.\n", file_path);
		return INIPARSER_EXIT_FAILURE;
	}
#else
	(*file) = fopen(file_path, "r");

	if (!(*file))
	{
		fprintf(stderr, "\n[INIParser] Error: No such file or directory '%s'.\n", file_path);
		return INIPARSER_EXIT_FAILURE;
	}
#endif

	return INIPARSER_EXIT_SUCCESS;
}

typedef struct INIFile {
	INIParserMasterContainer* data;
} INIFile;

#ifdef INIPARSER_IS_NEWLINE
#undef INIPARSER_IS_NEWLINE
#endif

#define INIPARSER_IS_NEWLINE(CHARACTER) (CHARACTER == '\n')

#ifdef INIPARSER_IS_COMMENT
#undef INIPARSER_IS_COMMENT
#endif

#define INIPARSER_IS_COMMENT(CHARACTER) (CHARACTER == ';')

#ifdef INIPARSER_IS_SECTION_START
#undef INIPARSER_IS_SECTION_START
#endif

#define INIPARSER_IS_SECTION_START(CHARACTER) (CHARACTER == '[')

#ifdef INIPARSER_IS_SECTION_END
#undef INIPARSER_IS_SECTION_END
#endif

#define INIPARSER_IS_SECTION_END(CHARACTER) (CHARACTER == ']')

#ifdef INIPARSER_IS_EQUALS_SIGN
#undef INIPARSER_IS_EQUALS_SIGN
#endif

#define INIPARSER_IS_EQUALS_SIGN(CHARACTER) (CHARACTER == '=')

static inline int _iniparser_whitespace_char(char character) {
	switch (character) {
	case ' ':
	case '\v':
	case '\t':
	case '\r':
	case '\f':
	case '\b':
	case '\a':
		return 1;
	default:
		return 0;
	}
}

static inline int _iniparser_is_section_key_char(char character) {
	if (48 <= character && character <= 57) {
		return 1;
	}

	if (65 <= character && character <= 90) {
		return 1;
	}

	if (97 <= character && character <= 122) {
		return 1;
	}

	return 0;
}

static int _iniparser_key_process(FILE* file, INIParserTextBuffer* buffer, char first_character, INIParserSectionContainer** current_section)
{
	int current_character = INIPARSER_NULL;

	_iniparser_textbuffer_clear(buffer);

	if (_iniparser_textbuffer_push(buffer, first_character))
	{
		return INIPARSER_EXIT_FAILURE;
	}

	int is_end = INIPARSER_NULL;

	while ((current_character = fgetc(file)) != EOF)
	{
		if (INIPARSER_IS_NEWLINE(current_character))
		{
			fprintf(stderr, "\n[INIParser] Error: Invalid key structure.\n");

			return INIPARSER_EXIT_FAILURE;
		}

		if (INIPARSER_IS_EQUALS_SIGN(current_character))
		{
			break;
		}

		if (!is_end && _iniparser_whitespace_char(current_character))
		{
			is_end = 1;
		}

		if (is_end && _iniparser_whitespace_char(current_character))
		{
			continue;
		}

		if (is_end || !_iniparser_is_section_key_char(current_character))
		{
			fprintf(stderr, "\n[INIParser] Error: Key name cannot contain characters other than letters and digits.\n");

			return INIPARSER_EXIT_FAILURE;
		}

		if (_iniparser_textbuffer_push(buffer, current_character))
		{
			return INIPARSER_EXIT_FAILURE;
		}
	}

	char* key = (char*)malloc(buffer->size + 1);

#if INIPARSER_SECURE_STRCPY == 1
	errno_t error = strcpy_s(key, buffer->size + 1, _iniparser_textbuffer_get_buffer(buffer));

	if (error != 0)
	{
		fprintf(stderr, "\n[INIParser] Error: An error occured while copying data.\n");

		return INIPARSER_EXIT_FAILURE;
	}

#else
	strcpy(key, _iniparser_textbuffer_get_buffer(buffer));
#endif

	_iniparser_textbuffer_clear(buffer);

	while ((current_character = fgetc(file)) != EOF)
	{
		if (INIPARSER_IS_NEWLINE(current_character))
		{
			break;
		}

		if (_iniparser_textbuffer_push(buffer, current_character))
		{
			return INIPARSER_EXIT_FAILURE;
		}
	}

	_iniparser_section_container_set((*current_section), key, _iniparser_textbuffer_get_buffer(buffer));

	free(key);

	key = INIPARSER_NULL;

	return INIPARSER_EXIT_SUCCESS;
}

static int _iniparser_section_process(FILE* file, INIParserTextBuffer* buffer, INIParserSectionContainer** current_section, INIParserMasterContainer* master)
{
	int current_character = INIPARSER_NULL;

	int is_closed = INIPARSER_NULL;

	_iniparser_textbuffer_clear(buffer);

	while ((current_character = fgetc(file)) != EOF)
	{
		if (INIPARSER_IS_NEWLINE(current_character))
		{
			break;
		}

		if (INIPARSER_IS_SECTION_END(current_character))
		{
			is_closed = 1;
			break;
		}

		if (!_iniparser_is_section_key_char(current_character))
		{
			fprintf(stderr, "\n[INIParser] Error: Section name cannot contain characters other than letters and digits.\n");

			return INIPARSER_EXIT_FAILURE;
		}

		if (_iniparser_textbuffer_push(buffer, current_character))
		{
			return INIPARSER_EXIT_FAILURE;
		}
	}

	if (is_closed)
	{
		if (buffer->size == INIPARSER_NULL)
		{
			fprintf(stderr, "\n[INIParser] Error: Section name cannot be empty.\n");

			return INIPARSER_EXIT_FAILURE;
		}

		*current_section = _iniparser_master_container_create_section(master, _iniparser_textbuffer_get_buffer(buffer));

		return INIPARSER_EXIT_SUCCESS;
	}
	else
	{
		return INIPARSER_EXIT_FAILURE;
	}
}

static void _iniparser_skip_line(FILE* file)
{
	int current_character = INIPARSER_NULL;

	while ((current_character = fgetc(file)) != EOF)
	{
		if (INIPARSER_IS_NEWLINE(current_character))
		{
			break;
		}
	}
}

static int _iniparser_config_process(FILE* file, INIFile* ini_file)
{
	int current_character = INIPARSER_NULL;

	INIParserTextBuffer buffer;

	if (_iniparser_textbuffer_create(&buffer))
	{
		return INIPARSER_EXIT_FAILURE;
	}

	INIParserMasterContainer* data = (INIParserMasterContainer*)malloc(sizeof(INIParserMasterContainer));

	if (_iniparser_master_container_create(data))
	{
		return INIPARSER_EXIT_FAILURE;
	}

	ini_file->data = data;

	INIParserSectionContainer* current_section = INIPARSER_NULL;

	while ((current_character = fgetc(file)) != EOF)
	{

		if (_iniparser_whitespace_char(current_character))
		{
			continue;
		}

		if (INIPARSER_IS_NEWLINE(current_character))
		{
			continue;
		}

		if (INIPARSER_IS_COMMENT(current_character))
		{
			_iniparser_skip_line(file);
			continue;
		}

		if (INIPARSER_IS_SECTION_START(current_character))
		{
			if (_iniparser_section_process(file, &buffer, &current_section, data))
			{
				return INIPARSER_EXIT_FAILURE;
			}
			else
			{
				continue;
			}
		}

		if (current_section == INIPARSER_NULL)
		{
			fprintf(stderr, "\n[INIParser] Error: Cannot add a key without a section.\n");

			return INIPARSER_EXIT_FAILURE;
		}

		if (_iniparser_key_process(file, &buffer, current_character, &current_section))
		{
			return INIPARSER_EXIT_FAILURE;
		}
		else
		{
			continue;
		}

		fprintf(stderr, "\n[INIParser] Error: Unexpected error occurred.\n");

		return INIPARSER_EXIT_FAILURE;
	}

	_iniparser_textbuffer_destroy(&buffer);

	return INIPARSER_EXIT_SUCCESS;
}

int inifile_create(INIFile* ini_file, const char* file_path)
{
	FILE* file = INIPARSER_NULL;

	if (_iniparser_secure_file_open(&file, file_path))
	{
		return INIPARSER_EXIT_FAILURE;
	}

	if (_iniparser_config_process(file, ini_file))
	{
		return INIPARSER_EXIT_FAILURE;
	}

	fclose(file);

	return INIPARSER_EXIT_SUCCESS;
};

void inifile_destroy(INIFile* ini_file)
{
	if (ini_file->data != INIPARSER_NULL)
	{
		_iniparser_master_container_destroy(ini_file->data);
	}

	free(ini_file->data);

	ini_file->data = INIPARSER_NULL;
};

const char* inifile_get(INIFile* ini_file, const char* section, const char* key)
{
	INIParserSectionContainer* section_data = _iniparser_master_container_get_section(ini_file->data, section);

	if (section_data != INIPARSER_NULL)
	{
		const char * value =  _iniparser_section_container_get(section_data, key);

		if (value != INIPARSER_NULL)
		{
			return value;
		}
		else
		{
			fprintf(stderr, "\n[INIParser] Error: Failed to find key: '%s' in section: '%s'.\n", key, section);

			fprintf(stderr, "[INIParser] at inifile_get() where section='%s', key='%s'.\n", section, key);
			
			return INIPARSER_NULL;
		}
	}
	else
	{
		fprintf(stderr, "[INIParser] at inifile_get() where section='%s', key='%s'.\n", section, key);

		return INIPARSER_NULL;
	}
};

void inifile_print_key(INIFile* ini_file, const char* section, const char* key)
{
	const char* value = inifile_get(ini_file, section, key);

	if (value != INIPARSER_NULL)
	{
		printf("key: '%s' value: '%s' type: 'string'\n", key, value);
	}
};


/*
int inifile_set(INIFile* ini_file, const char* section, const char* key, const char* value)
{
	INIParserSectionContainer* section_data = _iniparser_master_container_get_section(ini_file->data, section);
	if (section_data != INIPARSER_NULL)
	{
		_iniparser_section_container_set(section_data, key, value);
	}
	else
	{
		fprintf(stderr, "[INIParser] at inifile_set() where section='%s', key='%s' value='%s'.\n", section, key, value);
		return INIPARSER_NULL;
	}
};
*/

/*
static inline void _inifile_display_section(INIParserSectionContainer* section_data, const char* name)
{
	printf("section: '%s'\n", name);
	for (unsigned int i = 0; i < INIPARSER_SECTION_BUFFER_LIMIT; i++)
	{
		if (section_data->entries[i])
		{
			_inifile_display_key(section_data->entries[i]->key, section_data->entries[i]->value);
			//TODO
			//ADD NEXT
		}
	}
}
*/

/*
void inifile_print(INIFile* ini_file)
{
	for (unsigned int i = 0; i < INIPARSER_MASTER_BUFFER_LIMIT; i++)
	{
		if (ini_file->data->entries[i])
		{
			INIParserSectionContainer* section_data = ini_file->data->entries[i]->section;
			_inifile_display_section(section_data, ini_file->data->entries[i]->name);
			//TODO
			//ADD NEXT
		}
	}
};
*/

/*
void inifile_print_section(INIFile* ini_file, const char* name)
{
	INIParserSectionContainer* section_data = _iniparser_master_container_get_section(ini_file->data, name);
	if (section_data != INIPARSER_NULL)
	{
		_inifile_display_section(section_data, name);
	}
};
*/

/*
int inifile_save(const char* file_path)
{
	//TODO CALL GENERATE DATA 
	return INIPARSER_EXIT_SUCCESS;
};
*/

#endif /* INIPARSER_H */
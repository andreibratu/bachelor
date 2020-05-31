import * as React from 'react';
import {useEffect, useState} from 'react';
import {useStyletron} from 'baseui';
import {Input, StyledInput} from 'baseui/input';
import {KIND, Tag, VARIANT as TAG_VARIANT} from 'baseui/tag';

const InputReplacement = React.forwardRef(
    ({tags, removeTag, tagKind, ...restProps}, ref) => {
        const [css] = useStyletron();
        return (
            <div
                className={css({
                    flex: '1 1 0%',
                    flexWrap: 'wrap',
                    display: 'flex',
                    alignItems: 'center',
                })}
            >
                {tags?.map((tag, index) => (
                    <Tag
                        variant={TAG_VARIANT.solid}
                        kind={tagKind ? tagKind : KIND.primary}
                        onActionClick={() => removeTag(tag)}
                        key={index}
                    >
                        {tag}
                    </Tag>
                ))}
                <StyledInput ref={ref} {...restProps} />
            </div>
        );
    },
);


export default (props) => {
    const {tagKind, placeholder, controlCallback, controlValue, size} = props;
    const [value, setValue] = useState('');
    const [tags, setTags] = React.useState(controlValue);
    const addTag = (tag) => {
        setTags([...tags, tag]);
    };
    const removeTag = (tag) => {
        setTags(tags.filter(t => t !== tag));
    };
    useEffect(() => controlCallback(tags), [tags, controlCallback]);
    const handleKeyDown = event => {
        switch (event.keyCode) {
            // Enter, comma, or space triggers a new tag
            case 13:
            case 32:
                if (!value) return;
                addTag(value);
                setValue('');
                return;
            // Backspace
            case 8:
                if (value || !tags.length) return;
                removeTag(tags[tags.length - 1]);
                return;
            default:
                break
        }
    };

    return (
        <Input
            placeholder={tags?.length ? '' : placeholder}
            value={value}
            size={size}
            onChange={e => setValue(e.currentTarget.value)}
            overrides={{
                Input: {
                    style: {width: 'auto', flexGrow: 1},
                    component: InputReplacement,
                    props: {
                        tags: tags,
                        tagKind: tagKind,
                        removeTag: removeTag,
                        onKeyDown: handleKeyDown,
                    },
                },
            }}
        />
    );
};
